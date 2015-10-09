<?hh // strict

use \HHUnit\Assert\Assert;
use \HHUnit\Examples\AbstractExampleTest;
use \HHUnit\Runner\ClassLoader;

class ExpectExceptionTest extends AbstractExampleTest {
  <<Test, ExpectException("BadUsageException")>>
  public function this_will_throw_an_expected_exception() : void {
    MyCalculator::addOnlyPositiveIntegers(-3, 4);
  }
}
