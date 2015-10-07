<?hh // strict

namespace HHUnit\Runner;

use \HHUnit\Model\TestStatus;
use \HHUnit\Model\TestSuite;
use \HHUnit\UI\UIUtils;

class TestSuiteRunner {
  public static function run(TestSuite $testSuite) : void {
    UIUtils::printTestSuiteStart($testSuite);
    $runner = new TestSuiteRunner($testSuite);
    $runner->loadClass();
    $runner->runTests();
    $runner->unloadClass();
    UIUtils::printTestSuiteEnd($testSuite);
  }

  private TestSuite $testSuite;
  private array<string, \ReflectionMethod> $lifecycleMethods = array();
  private array<string, \ReflectionMethod> $testMethods = array();

  public function __construct(TestSuite $testSuite) {
    $this->testSuite = $testSuite;
  }

  public function loadClass() : void {
    // TODO check old globals vars & classes & methods and save the diff
    ClassLoader::loadClass($this->testSuite->getPath());
    $class = new \ReflectionClass($this->testSuite->getClassName());

    $allMethods = $class->getMethods();
    foreach($allMethods as $method) {
      if ($method->isPublic() && !$method->isStatic() && $method->getAttribute("Test") !== null) {
        $this->testMethods[$method->getName()] = $method;
      } else if ($method->isPublic() && $method->isStatic() && $method->getAttribute("SetUpClass") !== null) {
        $this->lifecycleMethods["setUpClass"] = $method;
      } else if ($method->isPublic() && $method->isStatic() && $method->getAttribute("TearDownClass") !== null) {
        $this->lifecycleMethods["tearDownClass"] = $method;
      } else if ($method->isPublic() && !$method->isStatic() && $method->getAttribute("SetUp") !== null) {
        $this->lifecycleMethods["setUp"] = $method;
      } else if ($method->isPublic() && !$method->isStatic() && $method->getAttribute("TearDown") !== null) {
        $this->lifecycleMethods["tearDown"] = $method;
      }
    }
    ksort($this->testMethods);
  }

  private static function isTestMethod(\ReflectionMethod $method) : bool {
    return $method->isPublic() && !$method->isStatic() && $method->getAttribute("Test") !== null;
  }

  public function unloadClass() : void {
    // TODO unload loaded global vars & classes & methods
  }

  public function runTests() : void {
    $class = new \ReflectionClass($this->testSuite->getClassName());
    $instance = $class->newInstance();

    // Let's setUp the suite
    try {
      if (array_key_exists("setUpClass", $this->lifecycleMethods)) {
        $this->lifecycleMethods["setUpClass"]->invoke($instance);
      }
    } catch(\Exception $e) {
      UIUtils::printError($this->testSuite->getClassName(), "setUpClass", $e);
      $this->testSuite->setStatus(TestStatus::ERROR);
      $this->testSuite->setEndTime(microtime(true));
      return;
    }

    // Actually run the tests
    $status = TestStatus::SKIPPED;
    foreach($this->testMethods as $method) {
      $testCaseRunner = new TestCaseRunner($class->getName(), $instance, $this->lifecycleMethods, $method);
      $testCase = $testCaseRunner->run();
      $this->testSuite->addTestCase($testCase);

      switch ($testCase->getStatus()) {
        case TestStatus::LOADING:
        case TestStatus::SKIPPED:
        // No op
        break;
        case TestStatus::SUCCESS:
        if ($status === TestStatus::SKIPPED) {
          $status = TestStatus::SUCCESS;
        }
        $this->testSuite->incNumSuccesses(1);
        break;
        case TestStatus::FAILURE:
        if ($status !== TestStatus::ERROR) {
          $status = TestStatus::FAILURE;
        }
        $this->testSuite->incNumFailures(1);
        break;
        case TestStatus::ERROR:
        $status = TestStatus::ERROR;
        $this->testSuite->incNumErrors(1);
        break;
      }
    }

    // Tear down the whole suite
    try {
      if (array_key_exists("tearDownClass", $this->lifecycleMethods)) {
        $this->lifecycleMethods["tearDownClass"]->invoke($instance);
      }
    } catch(\Exception $e) {
      UIUtils::printError($this->testSuite->getClassName(), "tearDownClass", $e);
      $this->testSuite->setStatus(TestStatus::ERROR);
    }

    $this->testSuite->setEndTime(microtime(true));
    $this->testSuite->setStatus($status);
  }
}
