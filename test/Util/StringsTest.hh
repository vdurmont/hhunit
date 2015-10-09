<?hh

use \HHUnit\Assert\Assert;
use \HHUnit\Util\Strings;

class StringsTest {
  <<Test>>
  public function startsWith_if_the_string_starts_with_the_needle() {
    $res = Strings::startsWith("test", "testing");
    Assert::isTrue($res);
  }

  <<Test>>
  public function startsWith_if_the_string_doesnt_start_with_the_needle() {
    $res = Strings::startsWith("test", "mytesting");
    Assert::isFalse($res);
  }
}
