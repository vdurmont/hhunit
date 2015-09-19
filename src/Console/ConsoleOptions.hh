<?hh

namespace HHUnit;

class ConsoleOptions {
  private string $testPath;

  public static function parse(array<string> $argv) : ConsoleOptions {
    // TODO add options? --help for example.
    if (count($argv) > 1) {
      $testPath = $argv[count($argv) - 1];
    } else {
      $testPath = ConsoleOptions::getCurrentDir();
    }
    return new ConsoleOptions($testPath);
  }

  private static function getCurrentDir() : string {
    return getcwd();
  }

  public function __construct(string $testPath) {
    $this->testPath = $testPath;
  }

  public function getTestPath() : string {
    return $this->testPath;
  }
}
