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

    $files = $this->fileService->scanDirectory($rootPath);
    foreach ($files as $file) {
      $fullFile = $rootPath."/".$file;
      if ($this->fileService->isFile($fullFile)) {
        if ($file === "HHUnitSetUp.hh") {
          $tree->setHasSetUp(TRUE);
        } else if ($file === "HHUnitTearDown.hh") {
          $tree->setHasTearDown(TRUE);
        } else if (Strings::endsWith(".hh", $file) || Strings::endsWith(".php", $file)) {
          $tree->addTestSuitePath($fullFile);
        }
      } else if ($file !== "." && $file !== "..") {
        $subTree = $this->buildTree($fullFile);
        $tree->addTestTree($subTree);
      }
    }

    return $tree;
  }
}
