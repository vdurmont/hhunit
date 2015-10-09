<?hh // strict

namespace HHUnit;

use \HHUnit\Core\IFileService;
use \HHUnit\Core\TestTreeBuilder;
use \HHUnit\Model\TestSummary;
use \HHUnit\Runner\TestTreeRunner;
use \HHUnit\UI\IPrinter;
use \HHUnit\UI\UIUtils;

/**
* HHUnit is the main entrypoint of the test framework.
*/
class HHUnit {
  // TODO real DI
  public IPrinter $printer;
  public IFileService $fileService;

  public function __construct(IPrinter $printer, IFileService $fileService) {
    // Init the DI components
    $this->printer = $printer;
    $this->fileService = $fileService;
  }

  public function run(string $testPath) : void {
    // TODO check the testPath

    $summary = new TestSummary($testPath);

    $builder = new TestTreeBuilder($this->fileService);
    $tree = $builder->buildTree($testPath);

    $runner = new TestTreeRunner($this->printer, $this->fileService);
    $runner->run($tree, $summary);

    $summary->setEndTime(microtime(true));

    $uiUtils = new UIUtils($this->printer);
    $uiUtils->printSummary($summary);
  }
}
