{
	description = "OpenGGL C++ Library";

	inputs.nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

	outputs = { self, nixpkgs }:
	let
		system = "x86_64-linux";
		pkgs = nixpkgs.legacyPackages.${system};
		libPath = with pkgs; lib.makeLibraryPath [
			libGL
			libxkbcommon
			wayland
			xorg.libX11
			xorg.libXcursor
			xorg.libXi
			xorg.libXrandr
		];
		openGGL = pkgs.stdenv.mkDerivation {
			pname = "OpenGGL";
			version = "0.1.0";

			src = ./.;

			# TODO: make some packages only available in build phase
			buildInputs = with pkgs; [ 
				assimp
				clang
				freeglut
				gcc
				glfw
				gnumake
				libGLU
			];

			buildPhase = ''
				make
			'';

			installPhase = ''
				mkdir --parents $out/include $out/lib
				cp --recursive include $out
				cp libOpenGGL.a libOpenGGLApp.a $out/lib/
			'';

			LD_LIBRARY_PATH = libPath + "/run/opengl-driver/lib:/run/opengl-driver-32/lib";
		};
	in {
		packages.x86_64-linux.openGGL = openGGL;
		devShells.x86_64-linux.default = openGGL;
		defaultPackage.x86_64-linux = openGGL;
	};
}
