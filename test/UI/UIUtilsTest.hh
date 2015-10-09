<?hh

use \HHUnit\Assert\Assert;
use \HHUnit\UI\UIUtils;

<<HHUnit>>
class UIUtilsTest {
  <<Test>>
  public function prettyDuration_with_zero() {
    Assert::equals("0ms", UIUtils::prettyDuration((float) 1442627656.045, (float) 1442627656.045));
  }

  <<Test>>
  public function prettyDuration_with_minutes_seconds_and_millis() {
    Assert::equals("1mn32s45ms", UIUtils::prettyDuration((float) 1442627656.045, (float) 1442627748.090));
  }

  <<Test>>
  public function prettyDuration_with_seconds_and_millis() {
    Assert::equals("32s45ms", UIUtils::prettyDuration((float) 1442627656.045, (float) 1442627688.090));
  }

  <<Test>>
  public function prettyDuration_with_millis() {
    Assert::equals("45ms", UIUtils::prettyDuration((float) 1442627656.045, (float) 1442627656.090));
  }
}
