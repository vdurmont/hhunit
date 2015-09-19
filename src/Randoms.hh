<?hh

namespace HHUnit;

class Randoms {
  public static function randomString(int $length = 32) : string {
    $str = "";
    while(strlen($str) < $length) {
      $str .= str_shuffle("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }
    return substr($str, 0, $length);
  }
}
