<?hh

namespace HHUnit;

use \HHUnit\UI\Colors;

class Test {
  public static function setUpClass() : void {
  }

  public function setUp() : void {
  }

  public function tearDown() : void {
  }

  public static function tearDownClass() : void {
  }

  public function assertEquals(mixed $expected, mixed $actual, ?string $message = "") : void {
    if ($expected != $actual) {
      throw new AssertionException(Test::getAssertionMessageForComparison($expected, $actual, $message));
    }
  }

  public function assertContains(mixed $needle, array<mixed> $haystack, ?string $message = "") : void {
    var_dump($needle);
    var_dump($haystack);
    if (!in_array($needle, $haystack)) {
      if ($message == null) {
        $message = "Unable to find in array"; // TODO error msg
      }
      throw new AssertionException(Colors::color("AssertionException: ".$message."\n", "yellow", null));
    }
  }

  public function assertTrue(bool $actual, ?string $message = "") : void {
    if (!$actual) {
      throw new AssertionException(Test::getAssertionMessageForComparison("TRUE", "FALSE", $message));
    }
  }

  public function assertFalse(bool $actual, ?string $message = "") : void {
    if ($actual) {
      throw new AssertionException(Test::getAssertionMessageForComparison("FALSE", "TRUE", $message));
    }
  }

  public function assertNull(mixed $actual, ?string $message = "") : void {
    $expected = null;
    if ($expected != $actual) {
      throw new AssertionException(Test::getAssertionMessageForComparison($expected, $actual, $message));
    }
  }

  public function assertNotNull(mixed $actual, ?string $message = "") : void {
    $notExpected = null;
    if ($notExpected == $actual) {
      throw new AssertionException(Test::getAssertionMessageForComparison("Not null", $actual, $message));
    }
  }

  public function fail(?string $message = null) : void {
    if ($message == null) {
      $message = "fail() was called.";
    }
    throw new AssertionException(Colors::color("AssertionException: ".$message."\n", "yellow", null));
  }

  private static function getAssertionMessageForComparison(mixed $expected, mixed $actual, ?string $message = null) : string {
    $str = Colors::color("AssertionException: ".($message == null ? "" : $message)."\n", "yellow", null);
    $str .= Colors::color("\tExpected: ".print_r($expected, true)."\n", "yellow", null);
    $str .= Colors::color("\tBut got: ".print_r($actual, true)."\n", "yellow", null);
    return $str;
  }
}
