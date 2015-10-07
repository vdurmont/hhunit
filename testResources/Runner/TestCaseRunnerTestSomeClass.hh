<?hh // strict

use \HHUnit\Exception\AssertionException;

class TestCaseRunnerTestSomeClass {
  <<Test, ExpectException("\HHUnit\Exception\AssertionException")>>
  public function test_throwing_expected_AssertionException() : void {
    throw new AssertionException();
  }

  <<Test>>
  public function test_throwing_Exception() : void {
    throw new \Exception();
  }

  <<Test, ExpectException("\Exception")>>
  public function test_throwing_expected_Exception() : void {
    throw new \Exception();
  }

  <<Test, ExpectException("\Exception")>>
  public function test_throwing_expected_subclass_of_Exception() : void {
    throw new AssertionException();
  }
}
