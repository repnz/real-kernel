import argparse
import os
import sys

def create_boot_file(bootloader, kernel, output):
    with open(bootloader, 'rb') as bootloader_file:
        boot_sector = bootloader_file.read()

    with open(output, 'wb') as boot_file:
        boot_file.write(boot_sector)

        with open(kernel, 'rb') as kernel_file:
            kernel_code = kernel_file.read()

        print 'Kernel Code Length is ', len(kernel_code)

        boot_file.write(kernel_code)

        # add padding
        sector_padding_length = 512 - (len(kernel_code) % 512)
        print 'Padding Length', sector_padding_length

        boot_file.write('\x00' * sector_padding_length)

    print 'Boot file created with size', os.path.getsize(output)


def parse_arguments():
    parser = argparse.ArgumentParser(description='Creates a boot file from bootloader and kernel code')
    parser.add_argument('bootloader', type=str, help='the path of the bootloader file')
    parser.add_argument('kernel', type=str, help='the path of the output kernel code file')
    parser.add_argument('output', type=str, help='the path of the output boot file')
    args = parser.parse_args()

    if not os.path.exists(args.bootloader):
        sys.stderr.write('Cannot find bootloader')
        exit(-1)

    if not os.path.exists(args.kernel):
        sys.stderr.write('Cannot find kernel file')
        exit(-1)

    return args.bootloader, args.kernel, args.output


def main():
    bootloader, kernel, output = parse_arguments()

    create_boot_file(bootloader, kernel, output)


if __name__ == '__main__':
    main()
