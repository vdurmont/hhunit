<?hh // strict

namespace HHUnit\Runner;

use \HHUnit\Exception\AssertionException;
use \HHUnit\Model\TestCase;
use \HHUnit\Model\TestStatus;
use \HHUnit\UI\UIUtils;

class TestCaseRunner<T> {
  private string $className;
  private T $instance;
  private array<string, \ReflectionMethod> $lifecycleMethods;
  private \ReflectionMethod $method;

  public function __construct(string $className, T $instance, array<string, \ReflectionMethod> $lifecycleMethods, \ReflectionMethod $method) {
    $this->instance = $instance;
    $this->className = $className;
    $this->lifecycleMethods = $lifecycleMethods;
    $this->method = $method;
  }

  public function run() : TestCase {
    $status = TestStatus::SKIPPED;

    $attribute = $this->method->getAttribute("ExpectException");
    $expectedClass = null;
    if ($attribute !== null && $attribute[0]) {
      $expectedClass = new \ReflectionClass($attribute[0]);
    }

    try {
      if (array_key_exists("setUp", $this->lifecycleMethods)) {
        $this->lifecycleMethods["setUp"]->invoke($this->instance);
      }
      $this->method->invoke($this->instance);
      if (array_key_exists("tearDown", $this->lifecycleMethods)) {
        $this->lifecycleMethods["tearDown"]->invoke($this->instance);
      }
      return new TestCase($this->method->getName(), TestStatus::SUCCESS);
    } catch(AssertionException $e) {
      return $this->handleException(TestStatus::FAILURE, $e, $expectedClass);
    } catch(\Exception $e) {
      return $this->handleException(TestStatus::ERROR, $e, $expectedClass);
    }
  }

  private function handleException(TestStatus $status, \Exception $e, ?\ReflectionClass $expected) : TestCase {
    if ($expected === null || !self::matchesExpected($e, $expected)) {
      if ($status === TestStatus::FAILURE) {
        UIUtils::printFailure($this->className, $this->method->getName(), $e);
      } else if ($status === TestStatus::ERROR) {
        UIUtils::printError($this->className, $this->method->getName(), $e);
      }
    } else {
      $status = TestStatus::SUCCESS;
    }
    return new TestCase($this->method->getName(), $status);
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
