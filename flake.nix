{
	description = "A Nix-flake-based C/C++ development environment";

	inputs.nixpkgs.url = "https://flakehub.com/f/NixOS/nixpkgs/0.1.*.tar.gz";

	outputs = { nixpkgs, ... }:
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
	in
	{
		devShells.x86_64-linux.default = pkgs.mkShell {
			nativeBuildInputs = with pkgs; [
				assimp
				clang
				freeglut
				gcc
				gcc
				glfw
				libGLU
			];

			LD_LIBRARY_PATH = libPath + "/run/opengl-driver/lib:/run/opengl-driver-32/lib";
		};
	};
}
