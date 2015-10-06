<?hh

namespace HHUnit\Runner;

use \HHUnit\HHUnit;
use \HHUnit\UI\Colors;
use \HHUnit\UI\Console;

class Runner {
  public function run() : void {
    $testPath = HHUnit::getInstance()->config->getTestPath();
    $testFiles = $this->getTestFiles($testPath);
    // TODO code me
  }

  public function getTestFiles(string $testPath) : array<string> {
    $testFiles = array();
    $fileService = HHUnit::getInstance()->fileService;

    if ($fileService->isDirectory($testPath) && $testPath != "." && $testPath != "..") {
      $files = $fileService->scanDirectory($testPath);
      foreach ($files as $file) {
        if ($file != "." && $file != "..") {
          $testFiles = array_merge($testFiles, $this->getTestFiles($testPath."/".$file));
        }
      }
    } else if ($fileService->isFile($testPath) && preg_match("/(.+)(Test)\.(hh|php)$/", $testPath) == 1) {
      $testFiles[] = $testPath;
    }

    return $testFiles;
  }
}
