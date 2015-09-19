<?hh

require_once(__DIR__."/../autoload_tests.hh");

use \HHUnit\Colors;
use \HHUnit\Test;

class ColorsTest extends Test {
  private static string $STR = "mystring";

  public function test_color_with_a_fg_and_bg() {
    $actual = Colors::color(ColorsTest::$STR, "red", "green");
    $this->assertEquals("\033[0;31m\033[42m".ColorsTest::$STR."\033[0m", $actual);
  }

  public function test_color_with_a_fg_and_no_bg() {
    $actual = Colors::color(ColorsTest::$STR, "red", null);
    $this->assertEquals("\033[0;31m".ColorsTest::$STR."\033[0m", $actual);
  }

  public function test_color_with_no_fg_and_a_bg() {
    $actual = Colors::color(ColorsTest::$STR, null, "green");
    $this->assertEquals("\033[42m".ColorsTest::$STR."\033[0m", $actual);
  }

  public function test_color_with_a_no_fg_nor_bg() {
    $actual = Colors::color(ColorsTest::$STR, null, null);
    $this->assertEquals(ColorsTest::$STR."\033[0m", $actual);
  }
}
