<?hh // strict

namespace HHUnit\UI;

use \HHUnit\Core\Config;
use \HHUnit\Core\IConfigLoader;
use \HHUnit\UI\ConsoleColors;
use \HHUnit\UI\IPrinter;

/**
* Manages all the access to the console.
*/
class Console implements IPrinter, IConfigLoader {
  private array<string> $argv;

  public function __construct(array<string> $argv) {
    $this->argv = $argv;
  }

  public function loadConfig() : Config {
    // TODO add options? --help for example.
    if (count($this->argv) > 1) {
      $testPath = realpath($this->argv[count($this->argv) - 1]);
    } else {
      $testPath = getcwd();
    }
    $config = new Config();
    $config->setTestPath($testPath);
    return $config;
  }

  public function write(string $str) : void {
    echo $str;
  }

  public function writeWithColor(string $str, string $color) : void {
    echo ConsoleColors::color($str, $color, null);
  }

  public function writeln(string $str) : void {
    $this->write($str."\n");
  }

  public function writelnWithColor(string $str, string $color) : void {
    $this->writeWithColor($str."\n", $color);
  }

  public function close(bool $isSuccess) : void {
    $code = $isSuccess ? 0 : 1;
    exit($code);
  }
}
