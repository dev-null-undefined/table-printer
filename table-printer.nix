{ lib, stdenv, fetchFromGitHub, cmake ? "" }:

stdenv.mkDerivation rec {
  pname = "table-printer";
  version = "v0.0.6";
  src = fetchFromGitHub {
    owner = "ThreshMain";
    repo = pname;
    rev = version;
    sha256 = "sha256-zIB10E75n5DYmrtjdGqyTWgC3lWf2e7/lWdUb0lYvFA=";
    fetchSubmodules = true;
  };
  nativeBuildInputs = [ cmake ];
  buildInputs = [ ];

  cmakeFlags = [  ];

  meta = with lib; {
    homepage = "https://github.com/ThreshMain/table-printer";
    description = "Table formatter utility";
    longDescription = ''
      Linux file content manipulation utility for printing formated table for better read ability
    '';
    platforms = platforms.linux;
  };
}
