<?hh // strict

namespace HHUnit\Runner;

use \HHUnit\Core\ClassLoader;
use \HHUnit\Core\IFileService;
use \HHUnit\Model\TestSuite;
use \HHUnit\Model\TestSummary;
use \HHUnit\Model\TestTree;
use \HHUnit\UI\IPrinter;

class TestTreeRunner {
  public function __construct(private IPrinter $printer, private IFileService $fileService) {
  }

  public function run(TestTree $testTree, TestSummary $summary) : void {
    // TODO save state (IStateService)

    // Load the HHUnitSetUp if it exists
    if ($testTree->hasSetUp()) {
      ClassLoader::loadClass($testTree->getPath()."/HHUnitSetUp.hh");
    }

    // Run the TestSuites
    foreach ($testTree->getTestSuitesPaths() as $testSuitePath) {
      $testSuiteRunner = new TestSuiteRunner($this->printer, $this->fileService);
      $testSuite = $testSuiteRunner->run($testSuitePath);
      if ($testSuite !== null) {
        $summary->addTestSuite($testSuite);
      }
    }

    // Run the subtrees
    foreach ($testTree->getTestTrees() as $subTree) {
      $testTreeRunner = new TestTreeRunner($this->printer, $this->fileService);
      $testTreeRunner->run($subTree, $summary);
    }

    // Load the HHUnitTearDown if it exists
    if ($testTree->hasTearDown()) {
      ClassLoader::loadClass($testTree->getPath()."/HHUnitTearDown.hh");
    }

    // TODO diff and clean state (IStateService)
  }
}
