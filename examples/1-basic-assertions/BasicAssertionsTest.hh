<?hh // strict

use \HHUnit\Assert\Assert;
use \HHUnit\Examples\AbstractExampleTest;

<<HHUnit>>
class BasicAssertionsTest extends AbstractExampleTest {
  <<Test>>
  public function add_with_2_positive_integers() : void {
    $result = MyCalculator::add(3, 4);
    Assert::equals(7, $result);
  }

  <<Test>>
  public function add_with_a_positive_integer_and_a_negative_integer() : void {
    $result = MyCalculator::add(3, -4);
    Assert::notEquals(0, $result);
  }

  <<Test>>
  public function isPositive_with_a_positive_integer() : void {
    $result = MyCalculator::isPositive(3);
    Assert::isTrue($result);
  }

  <<Test>>
  public function isPositive_with_a_negative_integer() : void {
    $result = MyCalculator::isPositive(-4);
    Assert::isFalse($result);
  }
}
