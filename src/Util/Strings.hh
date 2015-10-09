<?hh // strict

namespace HHUnit\Util;

class Strings {
  public static function endsWith(string $needle, string $haystack) : bool {
    $haystackLen = strlen($haystack);
    $needleLen = strlen($needle);
    if ($needleLen > $haystackLen) {
      return false;
    }
    return substr_compare($haystack, $needle, $haystackLen - $needleLen, $needleLen) === 0;
  }

  public static function startsWith(string $needle, string $haystack) : bool {
    $haystackLen = strlen($haystack);
    $needleLen = strlen($needle);
    if ($needleLen > $haystackLen) {
      return false;
    }
    return substr_compare($haystack, $needle, 0, $needleLen) === 0;
  }
}
