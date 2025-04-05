import os
import sys

def rename_h_to_hpp(directory="."):
	"""
	Recursively traverse the directory structure starting from the given directory
	and rename all files with .h extension to .hpp
	"""
	# Keep count of renamed files
	renamed_count = 0

	# Walk through all directories and files
	for root, dirs, files in os.walk(directory):
		# Check each file in the current directory
		for filename in files:
			# If the file has .h extension
			if filename.endswith(".h"):
				# Create the full path for the old and new filenames
				old_path = os.path.join(root, filename)
				new_path = os.path.join(root, filename[:-2] + ".hpp")

				try:
					# Rename the file
					os.rename(old_path, new_path)
					print(f"Renamed: {old_path} -> {new_path}")
					renamed_count += 1
				except Exception as e:
					print(f"Error renaming {old_path}: {e}")

	print(f"\nTotal files renamed: {renamed_count}")

if __name__ == "__main__":
	# If a directory is provided as a command-line argument, use it
	# Otherwise, use the current directory
	directory = sys.argv[1] if len(sys.argv) > 1 else "."

	print(f"Starting to rename .h files to .hpp in {os.path.abspath(directory)}")
	rename_h_to_hpp(directory)