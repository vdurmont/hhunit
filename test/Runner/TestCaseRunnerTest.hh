<?hh // strict

use \HHUnit\HHUnit;
use \HHUnit\Assert\Assert;
use \HHUnit\Core\ClassLoader;
use \HHUnit\Model\TestCase;
use \HHUnit\Model\TestStatus;
use \HHUnit\Runner\TestCaseRunner;
use \HHUnit\UI\IPrinter;

<<HHUnit>>
class TestCaseRunnerTest {
  <<SetUpClass>>
  public static function setUpClass() : void {
    ClassLoader::loadClass(__DIR__."/../../testResources/Runner/TestCaseRunnerTestSomeClass.hh");
    ClassLoader::loadClass(__DIR__."/../../testResources/MutedPrinter.hh");
  }

  <<Test>>
  public function run_with_an_AssertionException_that_was_expected() : void {
    $testCase = $this->testRun("test_throwing_expected_AssertionException");
    Assert::equals(TestStatus::SUCCESS, $testCase->getStatus());
  }

  <<Test>>
  public function run_with_an_Exception_that_was_expected() : void {
    $testCase = $this->testRun("test_throwing_expected_Exception");
    Assert::equals(TestStatus::SUCCESS, $testCase->getStatus());
  }

  <<Test>>
  public function run_with_an_Exception_that_was_not_expected() : void {
    $testCase = $this->testRun("test_throwing_Exception");
    Assert::equals(TestStatus::ERROR, $testCase->getStatus());
  }

  <<Test>>
  public function run_with_an_Exception_whose_superclass_was_expected() : void {
    $testCase = $this->testRun("test_throwing_expected_subclass_of_Exception");
    Assert::equals(TestStatus::SUCCESS, $testCase->getStatus());
  }

  <<Test>>
  public function tests_for_matchesExpected() : void {
    $ex = new \Exception();
    $assEx = new \HHUnit\Exception\AssertionException();
    $exClass = new \ReflectionClass("\Exception");
    $assExClass = new \ReflectionClass("\HHUnit\Exception\AssertionException");

    Assert::isTrue(TestCaseRunner::matchesExpected($ex, $exClass));
    Assert::isFalse(TestCaseRunner::matchesExpected($ex, $assExClass));
    Assert::isTrue(TestCaseRunner::matchesExpected($assEx, $assExClass));
    Assert::isTrue(TestCaseRunner::matchesExpected($assEx, $exClass));
  }

  private function testRun(string $methodName) : TestCase {
    $class = new \ReflectionClass("TestCaseRunnerTestSomeClass");
    $method = $class->getMethod($methodName);
    $instance = $class->newInstance();
    $runner = new TestCaseRunner(new MutedPrinter());
    return $runner->run("TestCaseRunnerTestSomeClass", $instance, array(), $method);
  }
}
