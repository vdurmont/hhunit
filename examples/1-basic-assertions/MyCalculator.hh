<?hh // strict

class MyCalculator {
  public static function add(int $a, int $b) : int {
    return $a + $b;
  }

  public static function isPositive(int $num) : bool {
    return $num > 0;
  }
}
