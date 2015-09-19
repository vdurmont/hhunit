<?hh

namespace HHUnit;

class Runner {
  private static array<string, bool> $RESERVED_NAMES = array(
    "setUp" => false,
    "tearDown" => false,
    "setUpClass" => true,
    "tearDownClass" => true
  );

  public static function run(string $filePath) : ?TestSuite {
    $className = Parser::parseFile($filePath);
    if ($className == null) {
      return null;
    }

    $runner = new Runner($filePath, $className);
    $runner->loadClass();
    $testSuite = $runner->runTests();
    $runner->unloadClass();
    return $testSuite;
  }

  private bool $testFound;
  private string $filePath;
  private string $className;
  private array<string, \ReflectionMethod> $lifecycleMethods = array();
  private array<string, \ReflectionMethod> $testMethods = array();

  public function __construct(string $filePath, string $className) {
    $this->filePath = $filePath;
    $this->className = $className;
    $this->testFound = false;
  }

  public function loadClass() : void {
    // TODO check old globals vars & classes & methods and save the diff
    require_once($this->filePath);
    $class = new \ReflectionClass($this->className);
    $this->testFound = Runner::isTest($class);

    if ($this->testFound) {
      $allMethods = $class->getMethods();
      foreach($allMethods as $method) {
        if (Runner::isTestMethod($method)) {
          $this->testMethods[$method->getName()] = $method;
        } else if (Runner::isLifecycleMethod($method)) {
          $this->lifecycleMethods[$method->getName()] = $method;
        }
      }
      ksort($this->testMethods);
    }
  }

  private static function isTest(\ReflectionClass $class) : bool {
    $found = false;
    do {
      $parentClass = $class->getParentClass();
      if ($parentClass instanceof \ReflectionClass) {
        if ($parentClass->getName() == "HHUnit\Test") {
          $found = true;
        }
      }
    } while(!$found && $parentClass instanceof ReflectionClass);
    return $found;
  }

  private static function isTestMethod(\ReflectionMethod $method) : bool {
    return $method->isPublic() && !$method->isStatic() && preg_match("/test(.+)/", $method->getName()) == 1;
  }

  private static function isLifecycleMethod(\ReflectionMethod $method) : bool {
    if (!$method->isPublic() || !array_key_exists($method->getName(), Runner::$RESERVED_NAMES)) {
      return false;
    }
    $reservedMethod = Runner::$RESERVED_NAMES[$method->getName()];
    return ($reservedMethod && $method->isStatic()) || (!$reservedMethod && !$method->isStatic());
  }

  public function unloadClass() : void {
    // TODO unload loaded global vars & classes & methods
  }

  public function runTests() : ?TestSuite {
    if (!$this->testFound) {
      return null;
    }

    echo Colors::color("Running ".$this->className."\n", "light_blue", null);
    $class = new \ReflectionClass($this->className);
    $instance = $class->newInstance();

    // Let's setUp the suite
    $startTime = microtime(true);
    try {
      $this->lifecycleMethods["setUpClass"]->invoke($instance);
    } catch(\Exception $e) {
      echo $e->getTraceAsString()."\n";
      echo Colors::color($this->className.": An error occurred in the setUpClass method.\n", "red", null);
      return new TestSuite($this->className, TestStatus::ERROR, array());
    }

    $status = TestStatus::SKIPPED;
    $testCases = array();
    $numSuccess = 0;
    $numFailure = 0;
    $numError = 0;
    foreach($this->testMethods as $method) {
      try {
        $this->lifecycleMethods["setUp"]->invoke($instance);
        $method->invoke($instance);
        $this->lifecycleMethods["tearDown"]->invoke($instance);
        if ($status == TestStatus::SKIPPED) {
          $status = TestStatus::SUCCESS;
        }
        $testCases[] = new TestCase($method->getName(), TestStatus::SUCCESS);
        $numSuccess++;
      } catch(AssertionException $e) {
        echo $e->getAsString()."\n";
        $status = TestStatus::FAILURE;
        $testCases[] = new TestCase($method->getName(), TestStatus::FAILURE);
        $numFailure++;
      } catch(\Exception $e) {
        $status = TestStatus::ERROR;
        $numError++;
        echo get_class($e).": ";
        echo $e->getMessage()."\n";
        echo $e->getTraceAsString()."\n";
        $testCases[] = new TestCase($method->getName(), TestStatus::ERROR);
      }
    }

    // Tear down the whole suite
    try {
      $this->lifecycleMethods["tearDownClass"]->invoke($instance);
    } catch(\Exception $e) {
      echo $e->getTraceAsString()."\n";
      echo Colors::color($this->className.": An error occurred in the tearDownClass method.\n", "red", null);
      return new TestSuite($this->className, TestStatus::ERROR, array());
    }
    $endTime = microtime(true);

    $str = $this->className.": ";
    $str .= $numSuccess." success, ";
    $str .= $numFailure." failures, ";
    $str .= $numError." errors, ";
    $str .= Console::prettyDuration($startTime, $endTime).".\n";
    $color = $numError > 0 || $numFailure > 0 ? "red" : "green";
    echo Colors::color($str, $color, null);
    return new TestSuite($this->className, $status, $testCases);
  }
}
