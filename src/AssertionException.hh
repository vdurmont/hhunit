<?hh

namespace HHUnit;

class AssertionException extends \Exception {
  private string $msg;

  public function __construct(string $message) {
    parent::__construct($message);
    $this->msg = $message;
  }

  public function getAsString() : string {
    return $this->msg.$this->getTraceAsString();
  }
}
