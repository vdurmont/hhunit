<?hh // strict

class MyCalculator {
  public static function add(int $a, int $b) : int {
    return $a + $b;
  }

  public static function isPositive(int $num) : bool {
    return $num > 0;
  }
  
  public static function addOnlyPositiveIntegers(int $a, int $b) : int {
    if ($a < 0 || $b < 0) {
      throw new BadUsageException();
    }
    return $a + $b;
  }
}
