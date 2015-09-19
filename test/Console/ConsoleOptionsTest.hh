<?hh

require_once(__DIR__."/../autoload_tests.hh");

use \HHUnit\ConsoleOptions;
use \HHUnit\Test;

class ConsoleOptionsTest extends Test {
  private static string $HHUNIT_PATH = "/path/to/hhunit/HHUnit.hh";

  public function test_parse_with_no_argument_set_the_current_directory_as_testPath() {
    $opts = ConsoleOptions::parse(array(ConsoleOptionsTest::$HHUNIT_PATH));
    $this->assertEquals(getcwd(), $opts->getTestPath());
  }

  public function test_parse_with_the_testPath() {
    $opts = ConsoleOptions::parse(array(
      ConsoleOptionsTest::$HHUNIT_PATH,
      "/path/to/my/project/test"
    ));
    $this->assertEquals("/path/to/my/project/test", $opts->getTestPath());
  }
}
