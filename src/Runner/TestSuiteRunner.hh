<?hh // strict

namespace HHUnit\Runner;

use \HHUnit\Core\ClassLoader;
use \HHUnit\Core\ClassParser;
use \HHUnit\Core\IFileService;
use \HHUnit\Core\TestSuiteBuilder;
use \HHUnit\Model\LifecycleIdentifier;
use \HHUnit\Model\TestStatus;
use \HHUnit\Model\TestSuite;
use \HHUnit\UI\IPrinter;
use \HHUnit\UI\UIUtils;

class TestSuiteRunner {
  private IFileService $fileService;
  private IPrinter $printer;
  private UIUtils $uiUtils;

  public function __construct(IPrinter $printer, IFileService $fileService) {
    $this->fileService = $fileService;
    $this->printer = $printer;
    $this->uiUtils = new UIUtils($printer);
  }

  public function run<T>(string $testSuitePath) : ?TestSuite<T> {
    // Load the TestSuite
    $builder = new TestSuiteBuilder($this->fileService);
    $testSuite = $builder->buildTestSuite($testSuitePath);
    
    if($testSuite === null) {
      return null;
    }

    $this->uiUtils->printTestSuiteStart($testSuite);

    // TODO save state (IStateService)

    // Run the tests
    $this->runTests($testSuite);

    // TODO diff and clean state (IStateService)

    $this->uiUtils->printTestSuiteEnd($testSuite);

    return $testSuite;
  }

  public function runTests<T>(TestSuite<T> $testSuite) : void {
    $instance = $testSuite->getInstance();

    // Let's setUp the suite
    try {
      if (array_key_exists(LifecycleIdentifier::SET_UP_CLASS, $testSuite->getLifecycleMethods())) {
        $testSuite->getLifecycleMethods()[LifecycleIdentifier::SET_UP_CLASS]->invoke($instance);
      }
    } catch(\Exception $e) {
      $this->uiUtils->printError($testSuite->getClass()->getName(), "setUpClass", $e);
      $testSuite->setStatus(TestStatus::ERROR);
      $testSuite->setEndTime(microtime(true));
      return;
    }

    // Actually run the tests
    $status = TestStatus::SKIPPED;
    $testMethods = $testSuite->getTestMethods();
    ksort($testMethods);
    foreach($testMethods as $method) {
      // TODO singleton
      $testCaseRunner = new TestCaseRunner($this->printer);
      $testCase = $testCaseRunner->run($testSuite->getClass()->getName(), $instance, $testSuite->getLifecycleMethods(), $method);
      $testSuite->addTestCase($testCase);

      switch ($testCase->getStatus()) {
        case TestStatus::LOADING:
        case TestStatus::SKIPPED:
        // No op
        break;
        case TestStatus::SUCCESS:
        if ($status === TestStatus::SKIPPED) {
          $status = TestStatus::SUCCESS;
        }
        $testSuite->incNumSuccesses(1);
        break;
        case TestStatus::FAILURE:
        if ($status !== TestStatus::ERROR) {
          $status = TestStatus::FAILURE;
        }
        $testSuite->incNumFailures(1);
        break;
        case TestStatus::ERROR:
        $status = TestStatus::ERROR;
        $testSuite->incNumErrors(1);
        break;
      }
    }

    // Tear down the whole suite
    try {
      if (array_key_exists(LifecycleIdentifier::TEAR_DOWN_CLASS, $testSuite->getLifecycleMethods())) {
        $testSuite->getLifecycleMethods()[LifecycleIdentifier::TEAR_DOWN_CLASS]->invoke($instance);
      }
    } catch(\Exception $e) {
      $this->uiUtils->printError($testSuite->getClass()->getName(), "tearDownClass", $e);
      $testSuite->setStatus(TestStatus::ERROR);
    }

    $testSuite->setEndTime(microtime(true));
    $testSuite->setStatus($status);
  }
}
