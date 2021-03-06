<?hh // strict

namespace HHUnit\Assert;

use \HHUnit\Exception\AssertionException;

/**
* Useful assertions for your tests!
*/
class Assert {
  /**
  * Tests that an object is in an array
  * @param $needle The object to search
  * @param $haystack The array where we will search the needle
  * @param $msg An optional message for the exception in case of a failure
  * @throws AssertionException if the needle is not in the haystack
  */
  public static function arrayContains<T>(T $needle, array<T> $haystack, ?string $msg = null) : void {
    $res = in_array($needle, $haystack);
    if ($res === FALSE) {
      $msg = $msg === null ? "Element not found" : $msg;
      $msg .= "\n\tExpected: An array that contains \"".print_r($needle, true)."\"";
      $msg .= "\n\tActual: ".print_r($haystack, true);
      $msg .= "\n";
      throw new AssertionException($msg);
    }
  }

  /**
  * Tests the equality between two objects.
  * @param $expected The expected object
  * @param $actual The actual object
  * @param $msg An optional message for the exception in case of a failure
  * @throws AssertionException if the objects are not equal
  */
  public static function equals<T>(?T $expected, ?T $actual, ?string $msg = null) : void {
    if ($expected !== $actual) {
      $msg = $msg === null ? "Comparison error" : $msg;
      $msg .= "\n\tExpected: ".print_r($expected, true);
      $msg .= "\n\tActual: ".print_r($actual, true);
      $msg .= "\n";
      throw new AssertionException($msg);
    }
  }

  /**
  * Fails when called!
  * @param $msg An optional message for the exception.
  * @throws AssertionException when called
  */
  public static function fail(?string $msg = null) : void {
    throw new AssertionException($msg === null ? "The test failed." : $msg);
  }

  /**
  * Tests that a boolean is false.
  * @param $actual The boolean
  * @param $msg An optional message for the exception in case of a failure
  * @throws AssertionException if the object is true
  */
  public static function isFalse(bool $actual, ?string $msg = null) : void {
    if ($actual) {
      $msg = $msg === null ? "Comparison error" : $msg;
      $msg .= "\n\tExpected: FALSE\n\tActual: TRUE\n";
      throw new AssertionException($msg);
    }
  }

  /**
  * Tests that an object is not null.
  * @param $actual The object
  * @param $msg An optional message for the exception in case of a failure
  * @throws AssertionException if the object is null
  */
  public static function isNotNull<T>(?T $actual, ?string $msg = null) : void {
    if ($actual === null) {
      $msg = $msg === null ? "Comparison error" : $msg;
      $msg .= "\n\tExpected: not null";
      $msg .= "\n\tActual: NULL\n";
      throw new AssertionException($msg);
    }
  }

  /**
  * Tests that an object is null.
  * @param $actual The object
  * @param $msg An optional message for the exception in case of a failure
  * @throws AssertionException if the object is not null
  */
  public static function isNull<T>(?T $actual, ?string $msg = null) : void {
    if ($actual !== null) {
      $msg = $msg === null ? "Comparison error" : $msg;
      $msg .= "\n\tExpected: null";
      $msg .= "\n\tActual: ".print_r($actual, true);
      $msg .= "\n";
      throw new AssertionException($msg);
    }
  }

  /**
  * Tests that a boolean is true.
  * @param $actual The boolean
  * @param $msg An optional message for the exception in case of a failure
  * @throws AssertionException if the object is false
  */
  public static function isTrue(bool $actual, ?string $msg = null) : void {
    if (!$actual) {
      $msg = $msg === null ? "Comparison error" : $msg;
      $msg .= "\n\tExpected: TRUE\n\tActual: FALSE\n";
      throw new AssertionException($msg);
    }
  }

  /**
  * Tests the inequality between two objects.
  * @param $notExpected The unexpected object
  * @param $actual The actual object
  * @param $msg An optional message for the exception in case of a failure
  * @throws AssertionException if the objects are equal
  */
  public static function notEquals<T>(?T $notExpected, ?T $actual, ?string $msg = null) : void {
    if ($notExpected === $actual) {
      $msg = $msg === null ? "The objects are both equal to: " : $msg;
      $msg .= print_r($notExpected, true);
      $msg .= "\n";
      throw new AssertionException($msg);
    }
  }

  /**
  * Tests that a string contains another string
  * @param $needle The substring we are going to search
  * @param $haystack The string where we will search the needle
  * @param $msg An optional message for the exception in case of a failure
  * @throws AssertionException if the needle is not in the haystack
  */
  public static function stringContains(string $needle, string $haystack, ?string $msg = null) : void {
    $res = strpos($haystack, $needle);
    if ($res === FALSE) {
      $msg = $msg === null ? "Substring not found" : $msg;
      $msg .= "\n\tExpected: A string that contains \"".$needle."\"";
      $msg .= "\n\tActual: ".$haystack;
      $msg .= "\n";
      throw new AssertionException($msg);
    }
  }
}
