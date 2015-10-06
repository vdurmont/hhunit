<?hh

require_once(__DIR__."/../autoload_tests.hh");

use \HHUnit\UI\Console;
use \HHUnit\Test;

class ConsoleTest extends Test {
  public function test_prettyDuration_with_minutes_seconds_and_millis() {
    $this->assertEquals("1mn32s45ms", Console::prettyDuration((float) 1442627656.045, (float) 1442627748.090));
  }

  public function test_prettyDuration_with_seconds_and_millis() {
    $this->assertEquals("32s45ms", Console::prettyDuration((float) 1442627656.045, (float) 1442627688.090));
  }

  public function test_prettyDuration_with_millis() {
    $this->assertEquals("45ms", Console::prettyDuration((float) 1442627656.045, (float) 1442627656.090));
  }
}
