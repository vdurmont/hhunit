<?hh

namespace HHUnit;

class TestSuite {
  private string $className;
  private int $numSuccess;
  private int $numTotal;
  private TestStatus $status;
  private array<TestCase> $testCases;

  public function __construct(string $className, TestStatus $status, array<TestCase> $testCases) {
    $this->className = $className;
    $this->status = $status;
    $this->testCases = $testCases;

    $this->numTotal = 0;
    $this->numSuccess = 0;
    foreach ($testCases as $testCase) {
      $this->numTotal++;
      if ($testCase->getStatus() == TestStatus::SUCCESS) {
        $this->numSuccess++;
      }
    }
  }

  public function getClassName() : string {
    return $this->className;
  }

  public function getStatus() : TestStatus {
    return $this->status;
  }

  public function getTestCases() : array<TestCase> {
    return $this->testCases;
  }

  public function getNumTotal() : int {
    return $this->numTotal;
  }

  public function getNumSuccess() : int {
    return $this->numSuccess;
  }
}
