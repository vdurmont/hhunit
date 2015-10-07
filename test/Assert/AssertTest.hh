<?hh

use \HHUnit\Assert\Assert;
use \HHUnit\Exception\AssertionException;

// Wow such inception.
class AssertTest {
  <<Test, ExpectException("\HHUnit\Exception\AssertionException")>>
  public function fail_fails() {
    Assert::fail();
  }

  <<Test>>
  public function fail_with_a_message_fails() {
    $failed = false;
    try {
      Assert::fail("My message");
    } catch(AssertionException $e) {
      Assert::stringContains("My message", $e->getMessage());
      $failed = true;
    }
    Assert::isTrue($failed);
  }

  <<Test, ExpectException("\HHUnit\Exception\AssertionException")>>
  public function isFalse_with_TRUE() {
    Assert::isFalse(TRUE);
  }

  <<Test>>
  public function isFalse_with_FALSE() {
    Assert::isFalse(FALSE);
  }

  <<Test, ExpectException("\HHUnit\Exception\AssertionException")>>
  public function isNull_with_not_null() {
    Assert::isNull("Hey!");
  }

  <<Test>>
  public function isNull_with_null() {
    Assert::isNull(null);
  }

  <<Test, ExpectException("\HHUnit\Exception\AssertionException")>>
  public function isTrue_with_FALSE() {
    Assert::isTrue(FALSE);
  }

  <<Test>>
  public function isTrue_with_TRUE() {
    Assert::isTrue(TRUE);
  }

  <<Test, ExpectException("\HHUnit\Exception\AssertionException")>>
  public function stringContains_with_wrong_string() {
    Assert::stringContains("hhunit", "My favorite test framework");
  }

  <<Test>>
  public function stringContains_with_a_substring() {
    Assert::stringContains("hhunit", "My favorite test framework is hhunit!");
  }
}
