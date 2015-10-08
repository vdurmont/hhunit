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
    $config = new Config();
    $testPath = self::resolveTestPath($this->argv);
    $configFile = $this->getConfigFile($testPath);
    $config->setTestPath($testPath);
    if (array_key_exists("set_up_tests_path", $configFile)) {
      $setUpTestsPath = $configFile["set_up_tests_path"];
      if (!is_file($setUpTestsPath)) {
        $setUpTestsPath = realpath($testPath."/".$setUpTestsPath);
      }
      $config->setSetUpTestsPath($setUpTestsPath);
    }
    return $config;
  }

  private function getConfigFile(string $testPath) : array<string, string> {
    // TODO recursively search for the file?
    $filePath = $testPath."/hhunit.json";
    if (is_file($filePath)) {
      $content = file_get_contents($filePath);
      $json = json_decode($content, true);
      if ($json !== null) {
        return $json;
      }
    }
    return array();
  }

  private static function resolveTestPath(array<string> $argv) : string {
    if (count($argv) > 1) {
      return realpath($argv[count($argv) - 1]);
    }
    return getcwd();
  }

  private static function addIfKeyExists(string $key, array<string, string> $configFile, array<string, string> $json) : void {
    if (array_key_exists($key, $json)) {
      $configFile[$key] = $json[$key];
    }
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
