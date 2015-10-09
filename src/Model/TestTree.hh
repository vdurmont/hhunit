<?hh // strict

namespace HHUnit\Model;

use \HHUnit\Exception\HHUnitException;

class TestTree {
  private string $path;
  private bool $hasSetUp;
  private bool $hasTearDown;
  private array<string> $testSuitesPaths;
  private array<TestTree> $testTrees;

  public function __construct(string $path) {
    $this->path = $path;
    $this->hasSetUp = FALSE;
    $this->hasTearDown = FALSE;
    $this->testSuitesPaths = array();
    $this->testTrees = array();
  }

  public function getPath() : string {
    return $this->path;
  }

  public function hasSetUp() : bool {
    return $this->hasSetUp;
  }

  public function setHasSetUp(bool $hasSetUp) : void {
    $this->hasSetUp = $hasSetUp;
  }

  public function hasTearDown() : bool {
    return $this->hasTearDown;
  }

  public function setHasTearDown(bool $hasTearDown) : void {
    $this->hasTearDown = $hasTearDown;
  }

  public function getTestSuitesPaths() : array<string> {
    return $this->testSuitesPaths;
  }

  public function addTestSuitePath(string $testSuitePath) : void {
    $this->testSuitesPaths[] = $testSuitePath;
  }

  public function addTestTree(TestTree $testTree) : void {
    $this->testTrees[] = $testTree;
  }

  public function getTestTrees() : array<TestTree> {
    return $this->testTrees;
  }

  public function getTestTree(string $path) : TestTree {
    $tree = null;
    foreach ($this->testTrees as $t) {
      if ($t->getPath() === $path) {
        return $t;
      }
    }
    throw new HHUnitException("Cannot find subtree at ".$path);
  }
}
