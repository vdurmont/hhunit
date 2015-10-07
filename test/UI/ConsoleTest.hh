<?hh

use \HHUnit\Assert\Assert;
use \HHUnit\UI\Console;

class ConsoleTest {
  // TODO code this test class with a mock of the FileSystem

  <<Test>>
  public function test() : void {
    Assert::isTrue(TRUE);
  }

  // <<Test>>
  // public function loadConfig_with_no_test_path() {
  //   $argv = array("/Users/vdurmont/development/hhunit/hhunit");
  //   $console = new Console($argv);
  //   $config = $console->loadConfig();
  //   Assert::equals("/Users/vdurmont/development/hhunit", $config->getTestPath());
  // }
  //
  // <<Test>>
  // public function loadConfig_with_a_relative_test_path() {
  //   $argv = array("/Users/vdurmont/development/hhunit/hhunit", "test");
  //   $console = new Console($argv);
  //   $config = $console->loadConfig();
  //   Assert::equals(getcwd()."/test", $config->getTestPath());
  // }
  //
  // <<Test>>
  // public function loadConfig_with_a_relative_test_path_to_a_file() {
  //   $argv = array("/Users/vdurmont/development/hhunit/hhunit", "test/UI/ConsoleTest.hh");
  //   $console = new Console($argv);
  //   $config = $console->loadConfig();
  //   Assert::equals(getcwd()."/test/UI/ConsoleTest.hh", $config->getTestPath());
  // }
  //
  // <<Test>>
  // public function loadConfig_with_an_absolute_test_path() {
  //   $argv = array("/Users/vdurmont/development/hhunit/hhunit", getcwd());
  //   $console = new Console($argv);
  //   $config = $console->loadConfig();
  //   Assert::equals(getcwd(), $config->getTestPath());
  // }
  //
  // <<Test>>
  // public function loadConfig_with_an_absolute_test_path_to_a_file() {
  //   $argv = array("/Users/vdurmont/development/hhunit/hhunit", getcwd()."/ConsoleTest.hh");
  //   $console = new Console($argv);
  //   $config = $console->loadConfig();
  //   Assert::equals(getcwd()."/ConsoleTest.hh", $config->getTestPath());
  // }
}
