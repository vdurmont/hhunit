<?hh // strict

namespace HHUnit\Model;

class TestCase {
  private TestStatus $status;
  private string $testName;

  public function __construct(string $testName, TestStatus $status) {
    $this->testName = $testName;
    $this->status = $status;
  }

  public function getStatus() : TestStatus {
    return $this->status;
  }

  public function setStatus(TestStatus $status) : void {
    $this->status = $status;
  }

  public function getTestName() : string {
    return $this->testName;
  }
}
