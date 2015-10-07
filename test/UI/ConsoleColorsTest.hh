<?hh

use \HHUnit\Assert\Assert;
use \HHUnit\UI\ConsoleColors;

class ConsoleColorsTest {
  private static string $STR = "mystring";

  <<Test>>
  public function color_with_a_fg_and_bg() {
    $actual = ConsoleColors::color(self::$STR, "red", "green");
    Assert::equals("\033[0;31m\033[42m".self::$STR."\033[0m", $actual);
  }

  <<Test>>
  public function color_with_a_fg_and_no_bg() {
    $actual = ConsoleColors::color(self::$STR, "red", null);
    Assert::equals("\033[0;31m".self::$STR."\033[0m", $actual);
  }

  <<Test>>
  public function color_with_no_fg_and_a_bg() {
    $actual = ConsoleColors::color(self::$STR, null, "green");
    Assert::equals("\033[42m".self::$STR."\033[0m", $actual);
  }

  <<Test>>
  public function color_with_a_no_fg_nor_bg() {
    $actual = ConsoleColors::color(self::$STR, null, null);
    Assert::equals(self::$STR."\033[0m", $actual);
  }
}
