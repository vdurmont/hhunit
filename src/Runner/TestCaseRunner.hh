<?hh // strict

namespace HHUnit\Runner;

use \HHUnit\Core\ClassLoader;
use \HHUnit\Exception\AssertionException;
use \HHUnit\Model\LifecycleIdentifier;
use \HHUnit\Model\TestCase;
use \HHUnit\Model\TestStatus;
use \HHUnit\UI\IPrinter;
use \HHUnit\UI\UIUtils;

class TestCaseRunner<T> {
  private UIUtils $uiUtils;

  public function __construct(IPrinter $printer) {
    $this->uiUtils = new UIUtils($printer);
  }

  public function run(string $className, T $instance, array<LifecycleIdentifier, \ReflectionMethod> $lifecycleMethods, \ReflectionMethod $method) : TestCase {
    $status = TestStatus::SKIPPED;

    $attribute = $method->getAttribute("ExpectException");
    $expectedClass = null;
    if ($attribute !== null && $attribute[0]) {
      $expectedClass = new \ReflectionClass($attribute[0]);
    }

    // TODO separate try-catches??
    try {
      if (array_key_exists(LifecycleIdentifier::SET_UP, $lifecycleMethods)) {
        $lifecycleMethods[LifecycleIdentifier::SET_UP]->invoke($instance);
      }
      $method->invoke($instance);
      if (array_key_exists(LifecycleIdentifier::TEAR_DOWN, $lifecycleMethods)) {
        $lifecycleMethods[LifecycleIdentifier::TEAR_DOWN]->invoke($instance);
      }
      return new TestCase($method->getName(), TestStatus::SUCCESS);
    } catch(AssertionException $e) {
      return $this->handleException($className, $method, TestStatus::FAILURE, $e, $expectedClass);
    } catch(\Exception $e) {
      return $this->handleException($className, $method, TestStatus::ERROR, $e, $expectedClass);
    }
  }

  private function handleException(string $className, \ReflectionMethod $method, TestStatus $status, \Exception $e, ?\ReflectionClass $expected) : TestCase {
    if ($expected === null || !self::matchesExpected($e, $expected)) {
      if ($status === TestStatus::FAILURE) {
        $this->uiUtils->printFailure($className, $method->getName(), $e);
      } else if ($status === TestStatus::ERROR) {
        $this->uiUtils->printError($className, $method->getName(), $e);
      }
    } else {
      $status = TestStatus::SUCCESS;
    }
    return new TestCase($method->getName(), $status);
  }

  public static function matchesExpected(\Exception $e, \ReflectionClass $expected) : bool {
    $actual = new \ReflectionClass(get_class($e));

    while ($actual !== null && $actual instanceof \ReflectionClass) {
      if ($actual->getName() === $expected->getName()) {
        return true;
      }
      $actual = $actual->getParentClass();
    }
    return false;
  }
}
