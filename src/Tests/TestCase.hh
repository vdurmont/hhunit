<?hh

namespace HHUnit;

class TestCase {
  private string $testName;
  private TestStatus $status;

  public function __construct(string $testName, TestStatus $status) {
    $this->testName = $testName;
    $this->status = $status;
  }

  public function getTestName() : string {
    return $this->testName;
  }

  public function getStatus() : TestStatus {
    return $this->status;
  }
}
