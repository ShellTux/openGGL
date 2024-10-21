#!/bin/sh
set -e

BASE_DIR="$(dirname "$0")"

usage() {
	echo "Usage: $0 <subcommand>"
	echo 'List of subcommands:'
	echo '  - template'
	exit 1
}

options='h'
long_options='help'
TEMP=$(getopt \
	--options $options \
	--long  $long_options \
	--name "$(basename "$0")" -- "$@")

# shellcheck disable=SC2181
if [ $? -ne 0 ]
then
	echo 'Terminating...' >&2
	exit 1
fi

# Note the quotes around "$TEMP": they are essential!
eval set -- "$TEMP"
unset TEMP

while true
do
	case "$1" in
		-h | --help)
			usage
			;;
		--)
			shift
			break
			;;
		*) # Option not dealt with
			echo 'Internal error!' >&2
			exit 1
			;;
	esac
done

template() {
	destination_dir="$(gum file --directory --height 8 "$1")"
	[ -z "$destination_dir" ] && exit 1

	app_name="$(gum input --placeholder 'App name (recommended kebab-case)')"
	[ -z "$app_name" ] && exit 1

	mkdir --parents "$destination_dir/$app_name"
	cp --recursive "$BASE_DIR"/template/* "$destination_dir/$app_name"
}

[ "$#" -lt 1 ] && usage

case "$1" in
	template) template "${2:-}" ;;
	*) usage ;;
esac
