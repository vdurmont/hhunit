<?hh // strict

namespace HHUnit\UI;

use \HHUnit\Core\IFileService;

class ConsoleParser {
  public function __construct(private IFileService $fileService) {
  }

  public function getTestPath(array<string> $argv) : string {
    if (count($argv) > 1) {
      return $this->fileService->getRealpath($argv[count($argv) - 1]);
    }
    return $this->fileService->getCwd();
  }
}
