<?hh

namespace HHUnit\Core;

use \HHUnit\UI\ConsoleOptions;

/**
 * Configuration for the tests.
 * Default values are initialized and can be overwritten by loading a config
 * file or specifying them in the command line interface.
 */
class Config {
  /**
   * The directory or file where the tests are going to run.
   */
  private string $testPath;

  public function __construct() {
      $this->testPath = getcwd();
  }

  public function initWithConsoleOptions(ConsoleOptions $opts) : void {
    // TODO code me
  }

  public function getTestPath() : string {
    return $this->testPath;
  }

  public function setTestPath(string $testPath) : void {
    $this->testPath = $testPath;
  }
}
