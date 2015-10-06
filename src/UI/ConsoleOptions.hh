<?hh

namespace HHUnit\UI;

/**
 * ConsoleOptions is a tool that helps parse the command line arguments.
 */
class ConsoleOptions {
  private string $testPath;

  public static function createFromCommandLine(array<string> $argv) : ConsoleOptions {
    // TODO add options? --help for example.
    if (count($argv) > 1) {
      $testPath = $argv[count($argv) - 1];
    } else {
      $testPath = getcwd();
    }
    return new ConsoleOptions($testPath);
  }

  public function __construct(string $testPath) {
    $this->testPath = $testPath;
  }

  public function getTestPath() : string {
    return $this->testPath;
  }
}
