<?hh // strict

namespace HHUnit\Model;

class TestSummary {
  private float $startTime;
  private float $endTime;
  private array<TestSuite<mixed>> $testSuites;

  public function __construct(private string $testPath) {
    $this->startTime = microtime(true);
    $this->endTime = $this->startTime;
    $this->testSuites = array();
  }

  public function getTestPath() : string {
    return $this->testPath;
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

  public function getTestSuites() : array<TestSuite<mixed>> {
    return $this->testSuites;
  }

  public function addTestSuite(TestSuite<mixed> $testSuite) : void {
    $this->testSuites[] = $testSuite;
  }
}
