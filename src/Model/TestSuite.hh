<?hh // strict

namespace HHUnit\Model;

class TestSuite {
  private TestStatus $status;
  private string $path;
  private string $className;

  private array<TestCase> $testCases;

  private float $startTime;
  private float $endTime;

  private int $numSuccesses;
  private int $numFailures;
  private int $numErrors;

  public function __construct(string $path, string $className) {
    $this->status = TestStatus::LOADING;
    $this->path = $path;
    $this->className = $className;
    $this->testCases = array();

    // Init default values
    $this->startTime = microtime(true);
    $this->endTime = $this->startTime;
    $this->numSuccesses = 0;
    $this->numFailures = 0;
    $this->numErrors = 0;
  }

  public function getStatus() : TestStatus {
    return $this->status;
  }

  public function setStatus(TestStatus $status) : void {
    $this->status = $status;
  }

  public function getPath() : string {
    return $this->path;
  }

  public function getClassName() : string {
    return $this->className;
  }

  public function getTestCases() : array<TestCase> {
    return $this->testCases;
  }

  public function addTestCase(TestCase $testCase) : void {
    $this->testCases[] = $testCase;
  }

  public function getStartTime() : float {
    return $this->startTime;
  }

  public function getEndTime() : float {
    return $this->endTime;
  }

  public function setEndTime(float $endTime) : void {
    $this->endTime = $endTime;
  }

  public function getNumSuccesses() : int {
    return $this->numSuccesses;
  }

  public function incNumSuccesses(int $num) : void {
    $this->numSuccesses += $num;
  }

  public function getNumFailures() : int {
    return $this->numFailures;
  }

  public function incNumFailures(int $num) : void {
    $this->numFailures += $num;
  }

  public function getNumErrors() : int {
    return $this->numErrors;
  }

  public function incNumErrors(int $num) : void {
    $this->numErrors += $num;
  }
}
