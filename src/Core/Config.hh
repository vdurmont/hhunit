<?hh // strict

namespace HHUnit\Core;

use \HHUnit\HHUnit;

/**
* This class holds the configuration for the tests.
*/
class Config {
  private ?string $setUpTestsPath;
  private ?string $tearDownTestsPath;
  private string $testPath;

  public function __construct() {
    $this->testPath = HHUnit::getFileService()->getCwd();
  }

  public function getSetUpTestsPath() : ?string {
    return $this->setUpTestsPath;
  }

  public function setSetUpTestsPath(string $setUpTestsPath) : void {
    $this->setUpTestsPath = $setUpTestsPath;
  }

  public function getTearDownTestsPath() : ?string {
    return $this->tearDownTestsPath;
  }

  public function getTestPath() : string {
    return $this->testPath;
  }

  public function setTestPath(string $testPath) : void {
    $this->testPath = $testPath;
  }
}
