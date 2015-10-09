<?hh

use \HHUnit\Assert\Assert;
use \HHUnit\UI\ConsoleParser;

class ConsoleParserTest {
  <<SetUpClass>>
  public function setUpClass() : void {
    ClassLoader::loadClass(__DIR__."../../testResources/InMemoryFileService.hh");
  }

  <<Test>>
  public function loadConfig_with_no_test_path() {
    $argv = array("/Users/vdurmont/development/hhunit/hhunit");
    $fs = new InMemoryFileService();
    $fs->setCwd("/my/project");
    $console = new ConsoleParser($fs);
    Assert::equals("/my/project", $console->getTestPath($argv));
  }

  <<Test>>
  public function loadConfig_with_a_relative_test_path() {
    $argv = array("/Users/vdurmont/development/hhunit/hhunit", "test");
    $fs = new InMemoryFileService();
    $fs->setCwd("/my/project");
    $console = new ConsoleParser($fs);
    Assert::equals("/my/project/test", $console->getTestPath($argv));
  }

  <<Test>>
  public function loadConfig_with_a_relative_test_path_to_a_file() {
    $argv = array("/Users/vdurmont/development/hhunit/hhunit", "test/UI/ConsoleTest.hh");
    $fs = new InMemoryFileService();
    $fs->setCwd("/my/project");
    $console = new ConsoleParser($fs);
    Assert::equals("/my/project/test/UI/ConsoleTest.hh", $console->getTestPath($argv));
  }

  <<Test>>
  public function loadConfig_with_an_absolute_test_path() {
    $argv = array("/Users/vdurmont/development/hhunit/hhunit", "/my/project/test");
    $fs = new InMemoryFileService();
    $fs->setCwd("/my/project");
    $console = new ConsoleParser($fs);
    Assert::equals("/my/project/test", $console->getTestPath($argv));
  }

  <<Test>>
  public function loadConfig_with_an_absolute_test_path_to_a_file() {
    $argv = array("/Users/vdurmont/development/hhunit/hhunit", "/my/project/test/SomeTest.hh");
    $fs = new InMemoryFileService();
    $fs->setCwd("/my/project");
    $console = new ConsoleParser($fs);
    Assert::equals("/my/project/test/SomeTest.hh", $console->getTestPath($argv));
  }
}
