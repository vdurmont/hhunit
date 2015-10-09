<?hh // strict

namespace HHUnit\Core;

use \HHUnit\Core\IFileService;
use \HHUnit\Model\TestTree;
use \HHUnit\Util\Strings;

class TestTreeBuilder {
  private IFileService $fileService;

  public function __construct(IFileService $fileService) {
    $this->fileService = $fileService;
  }

  public function buildTree(string $rootPath) : TestTree {
    while (Strings::endsWith("/", $rootPath)) {
      $rootPath = substr($rootPath, 0, strlen($rootPath) - 1);
    }

    $tree = new TestTree($rootPath);
    if ($this->fileService->isFile($rootPath."/HHUnitSetUp.hh")) {
      $tree->setHasSetUp(TRUE);
    }
    if ($this->fileService->isFile($rootPath."/HHUnitTearDown.hh")) {
      $tree->setHasTearDown(TRUE);
    }

    $files = $this->fileService->scanDirectory($rootPath);
    foreach ($files as $file) {
      $fullFile = $rootPath."/".$file;
      if ($this->fileService->isFile($fullFile)) {
        if (Strings::endsWith("Test.hh", $fullFile) || Strings::endsWith("Test.php", $fullFile)) {
          $tree->addTestSuitePath($fullFile);
        }
      } else {
        $subTree = $this->buildTree($fullFile);
        $tree->addTestTree($subTree);
      }
    }

    return $tree;
  }
}
