/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Licensing Unit Tests
 *
 * Copyright 2011 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "license.h"

#include <freerdp/freerdp.h>
#include <freerdp/utils/hexdump.h>
#include <freerdp/utils/stream.h>

#include "test_license.h"

rdpRdp* rdp;
rdpLicense* license;

int init_license_suite(void)
{
	rdp = rdp_new(NULL);
	license = rdp->license;
	return 0;
}

int clean_license_suite(void)
{
	rdp_free(rdp);
	return 0;
}

int add_license_suite(void)
{
	add_test_suite(license);

	add_test_function(license);
	//add_test_function(license_generate_keys);
	//add_test_function(license_encrypt_premaster_secret);
	add_test_function(license_decrypt_platform_challenge);

	return 0;
}

/* Server License Request (2200 bytes) */

BYTE server_license_request[2200] =
	"\x01\x03\x98\x08\x84\xef\xae\x20\xb1\xd5\x9e\x36\x49\x1a\xe8\x2e"
	"\x0a\x99\x89\xac\x49\xa6\x47\x4f\x33\x9b\x5a\xb9\x95\x03\xa6\xc6"
	"\xc2\x3c\x3f\x61\x00\x00\x06\x00\x2c\x00\x00\x00\x4d\x00\x69\x00"
	"\x63\x00\x72\x00\x6f\x00\x73\x00\x6f\x00\x66\x00\x74\x00\x20\x00"
	"\x43\x00\x6f\x00\x72\x00\x70\x00\x6f\x00\x72\x00\x61\x00\x74\x00"
	"\x69\x00\x6f\x00\x6e\x00\x00\x00\x08\x00\x00\x00\x41\x00\x30\x00"
	"\x32\x00\x00\x00\x0d\x00\x04\x00\x01\x00\x00\x00\x03\x00\x12\x08"
	"\x02\x00\x00\x80\x02\x00\x00\x00\xf5\x02\x00\x00\x30\x82\x02\xf1"
	"\x30\x82\x01\xdd\xa0\x03\x02\x01\x02\x02\x08\x01\x9e\x24\xa2\xf2"
	"\xae\x90\x80\x30\x09\x06\x05\x2b\x0e\x03\x02\x1d\x05\x00\x30\x32"
	"\x31\x30\x30\x13\x06\x03\x55\x04\x03\x1e\x0c\x00\x52\x00\x4f\x00"
	"\x44\x00\x45\x00\x4e\x00\x54\x30\x19\x06\x03\x55\x04\x07\x1e\x12"
	"\x00\x57\x00\x4f\x00\x52\x00\x4b\x00\x47\x00\x52\x00\x4f\x00\x55"
	"\x00\x50\x30\x1e\x17\x0d\x37\x30\x30\x35\x32\x37\x30\x31\x31\x31"
	"\x30\x33\x5a\x17\x0d\x34\x39\x30\x35\x32\x37\x30\x31\x31\x31\x30"
	"\x33\x5a\x30\x32\x31\x30\x30\x13\x06\x03\x55\x04\x03\x1e\x0c\x00"
	"\x52\x00\x4f\x00\x44\x00\x45\x00\x4e\x00\x54\x30\x19\x06\x03\x55"
	"\x04\x07\x1e\x12\x00\x57\x00\x4f\x00\x52\x00\x4b\x00\x47\x00\x52"
	"\x00\x4f\x00\x55\x00\x50\x30\x82\x01\x22\x30\x0d\x06\x09\x2a\x86"
	"\x48\x86\xf7\x0d\x01\x01\x01\x05\x00\x03\x82\x01\x0f\x00\x30\x82"
	"\x01\x0a\x02\x82\x01\x01\x00\x88\xad\x7c\x8f\x8b\x82\x76\x5a\xbd"
	"\x8f\x6f\x62\x18\xe1\xd9\xaa\x41\xfd\xed\x68\x01\xc6\x34\x35\xb0"
	"\x29\x04\xca\x4a\x4a\x1c\x7e\x80\x14\xf7\x8e\x77\xb8\x25\xff\x16"
	"\x47\x6f\xbd\xe2\x34\x3d\x2e\x02\xb9\x53\xe4\x33\x75\xad\x73\x28"
	"\x80\xa0\x4d\xfc\x6c\xc0\x22\x53\x1b\x2c\xf8\xf5\x01\x60\x19\x7e"
	"\x79\x19\x39\x8d\xb5\xce\x39\x58\xdd\x55\x24\x3b\x55\x7b\x43\xc1"
	"\x7f\x14\x2f\xb0\x64\x3a\x54\x95\x2b\x88\x49\x0c\x61\x2d\xac\xf8"
	"\x45\xf5\xda\x88\x18\x5f\xae\x42\xf8\x75\xc7\x26\x6d\xb5\xbb\x39"
	"\x6f\xcc\x55\x1b\x32\x11\x38\x8d\xe4\xe9\x44\x84\x11\x36\xa2\x61"
	"\x76\xaa\x4c\xb4\xe3\x55\x0f\xe4\x77\x8e\xde\xe3\xa9\xea\xb7\x41"
	"\x94\x00\x58\xaa\xc9\x34\xa2\x98\xc6\x01\x1a\x76\x14\x01\xa8\xdc"
	"\x30\x7c\x77\x5a\x20\x71\x5a\xa2\x3f\xaf\x13\x7e\xe8\xfd\x84\xa2"
	"\x5b\xcf\x25\xe9\xc7\x8f\xa8\xf2\x8b\x84\xc7\x04\x5e\x53\x73\x4e"
	"\x0e\x89\xa3\x3c\xe7\x68\x5c\x24\xb7\x80\x53\x3c\x54\xc8\xc1\x53"
	"\xaa\x71\x71\x3d\x36\x15\xd6\x6a\x9d\x7d\xde\xae\xf9\xe6\xaf\x57"
	"\xae\xb9\x01\x96\x5d\xe0\x4d\xcd\xed\xc8\xd7\xf3\x01\x03\x38\x10"
	"\xbe\x7c\x42\x67\x01\xa7\x23\x02\x03\x01\x00\x01\xa3\x13\x30\x11"
	"\x30\x0f\x06\x03\x55\x1d\x13\x04\x08\x30\x06\x01\x01\xff\x02\x01"
	"\x00\x30\x09\x06\x05\x2b\x0e\x03\x02\x1d\x05\x00\x03\x82\x01\x01"
	"\x00\x81\xdd\xd2\xd3\x33\xd4\xa3\xb6\x8e\x6e\x7d\x9f\xfd\x73\x9f"
	"\x31\x0b\xdd\x42\x82\x3f\x7e\x21\xdf\x28\xcc\x59\xca\x6a\xc0\xa9"
	"\x3d\x30\x7d\xe1\x91\xdb\x77\x6b\x8b\x10\xe6\xfd\xbc\x3c\xa3\x58"
	"\x48\xc2\x36\xdd\xa0\x0b\xf5\x8e\x13\xda\x7b\x04\x08\x44\xb4\xf2"
	"\xa8\x0d\x1e\x0b\x1d\x1a\x3f\xf9\x9b\x4b\x5a\x54\xc5\xb3\xb4\x03"
	"\x93\x75\xb3\x72\x5c\x3d\xcf\x63\x0f\x15\xe1\x64\x58\xde\x52\x8d"
	"\x97\x79\x0e\xa4\x34\xd5\x66\x05\x58\xb8\x6e\x79\xb2\x09\x86\xd5"
	"\xf0\xed\xc4\x6b\x4c\xab\x02\xb8\x16\x5f\x3b\xed\x88\x5f\xd1\xde"
	"\x44\xe3\x73\x47\x21\xf7\x03\xce\xe1\x6d\x10\x0f\x95\xcf\x7c\xa2"
	"\x7a\xa6\xbf\x20\xdb\xe1\x93\x04\xc8\x5e\x6a\xbe\xc8\x01\x5d\x27"
	"\xb2\x03\x0f\x66\x75\xe7\xcb\xea\x8d\x4e\x98\x9d\x22\xed\x28\x40"
	"\xd2\x7d\xa4\x4b\xef\xcc\xbf\x01\x2a\x6d\x3a\x3e\xbe\x47\x38\xf8"
	"\xea\xa4\xc6\x30\x1d\x5e\x25\xcf\xfb\xe8\x3d\x42\xdd\x29\xe8\x99"
	"\x89\x9e\xbf\x39\xee\x77\x09\xd9\x3e\x8b\x52\x36\xb6\xbb\x8b\xbd"
	"\x0d\xb2\x52\xaa\x2c\xcf\x38\x4e\x4d\xcf\x1d\x6d\x5d\x25\x17\xac"
	"\x2c\xf6\xf0\x65\x5a\xc9\xfe\x31\x53\xb4\xf0\x0c\x94\x4e\x0d\x54"
	"\x8e\xfd\x04\x00\x00\x30\x82\x04\xf9\x30\x82\x03\xe5\xa0\x03\x02"
	"\x01\x02\x02\x05\x01\x00\x00\x00\x02\x30\x09\x06\x05\x2b\x0e\x03"
	"\x02\x1d\x05\x00\x30\x32\x31\x30\x30\x13\x06\x03\x55\x04\x03\x1e"
	"\x0c\x00\x52\x00\x4f\x00\x44\x00\x45\x00\x4e\x00\x54\x30\x19\x06"
	"\x03\x55\x04\x07\x1e\x12\x00\x57\x00\x4f\x00\x52\x00\x4b\x00\x47"
	"\x00\x52\x00\x4f\x00\x55\x00\x50\x30\x1e\x17\x0d\x30\x37\x30\x35"
	"\x32\x36\x31\x32\x34\x35\x35\x33\x5a\x17\x0d\x33\x38\x30\x31\x31"
	"\x39\x30\x33\x31\x34\x30\x37\x5a\x30\x81\x92\x31\x81\x8f\x30\x23"
	"\x06\x03\x55\x04\x03\x1e\x1c\x00\x6e\x00\x63\x00\x61\x00\x6c\x00"
	"\x72\x00\x70\x00\x63\x00\x3a\x00\x52\x00\x4f\x00\x44\x00\x45\x00"
	"\x4e\x00\x54\x30\x23\x06\x03\x55\x04\x07\x1e\x1c\x00\x6e\x00\x63"
	"\x00\x61\x00\x6c\x00\x72\x00\x70\x00\x63\x00\x3a\x00\x52\x00\x4f"
	"\x00\x44\x00\x45\x00\x4e\x00\x54\x30\x43\x06\x03\x55\x04\x05\x1e"
	"\x3c\x00\x31\x00\x42\x00\x63\x00\x4b\x00\x65\x00\x62\x00\x68\x00"
	"\x70\x00\x58\x00\x5a\x00\x74\x00\x4c\x00\x71\x00\x4f\x00\x37\x00"
	"\x53\x00\x51\x00\x6e\x00\x42\x00\x70\x00\x52\x00\x66\x00\x75\x00"
	"\x64\x00\x64\x00\x64\x00\x59\x00\x3d\x00\x0d\x00\x0a\x30\x82\x01"
	"\x1e\x30\x09\x06\x05\x2b\x0e\x03\x02\x0f\x05\x00\x03\x82\x01\x0f"
	"\x00\x30\x82\x01\x0a\x02\x82\x01\x01\x00\xc8\x90\x6b\xf0\xc6\x58"
	"\x81\xa6\x89\x1c\x0e\xf2\xf6\xd9\x82\x12\x71\xa5\x6e\x51\xdb\xe0"
	"\x32\x66\xaa\x91\x77\x0e\x88\xab\x44\xb7\xd3\x97\xda\x78\x8f\x0e"
	"\x44\x26\x46\x7f\x16\xd4\xc6\x63\xeb\xca\x55\xe5\x4e\x8b\x2d\xa6"
	"\x6d\x83\x95\xa7\xa8\x6a\xfa\xd0\xbe\x26\x80\xae\xab\x0a\x64\x90"
	"\x32\x8c\xdf\x5c\xf8\xf9\xd0\x7e\xd1\x6b\x3a\x29\x7e\x7d\xbd\x02"
	"\xa3\x86\x6c\xfd\xa5\x35\x71\xda\x21\xb4\xee\xa4\x97\xf3\xa8\xb2"
	"\x12\xdb\xa4\x27\x57\x36\xc9\x08\x22\x5c\x54\xf7\x99\x7b\xa3\x2f"
	"\xb8\x5c\xd5\x16\xb8\x19\x27\x6b\x71\x97\x14\x5b\xe8\x1f\x23\xe8"
	"\x5c\xb8\x1b\x73\x4b\x6e\x7a\x03\x13\xff\x97\xe9\x62\xb9\x4a\xa0"
	"\x51\x23\xc3\x6c\x32\x3e\x02\xf2\x63\x97\x23\x1c\xc5\x78\xd8\xfc"
	"\xb7\x07\x4b\xb0\x56\x0f\x74\xdf\xc5\x56\x28\xe4\x96\xfd\x20\x8e"
	"\x65\x5a\xe6\x45\xed\xc1\x05\x3e\xab\x58\x55\x40\xaf\xe2\x47\xa0"
	"\x4c\x49\xa3\x8d\x39\xe3\x66\x5f\x93\x33\x6d\xf8\x5f\xc5\x54\xe5"
	"\xfb\x57\x3a\xde\x45\x12\xb5\xc7\x05\x4b\x88\x1f\xb4\x35\x0f\x7c"
	"\xc0\x75\x17\xc6\x67\xdd\x48\x80\xcb\x0a\xbe\x9d\xf6\x93\x60\x65"
	"\x34\xeb\x97\xaf\x65\x6d\xdf\xbf\x6f\x5b\x02\x03\x01\x00\x01\xa3"
	"\x82\x01\xbf\x30\x82\x01\xbb\x30\x14\x06\x09\x2b\x06\x01\x04\x01"
	"\x82\x37\x12\x04\x01\x01\xff\x04\x04\x01\x00\x05\x00\x30\x3c\x06"
	"\x09\x2b\x06\x01\x04\x01\x82\x37\x12\x02\x01\x01\xff\x04\x2c\x4d"
	"\x00\x69\x00\x63\x00\x72\x00\x6f\x00\x73\x00\x6f\x00\x66\x00\x74"
	"\x00\x20\x00\x43\x00\x6f\x00\x72\x00\x70\x00\x6f\x00\x72\x00\x61"
	"\x00\x74\x00\x69\x00\x6f\x00\x6e\x00\x00\x00\x30\x81\xcd\x06\x09"
	"\x2b\x06\x01\x04\x01\x82\x37\x12\x05\x01\x01\xff\x04\x81\xbc\x00"
	"\x30\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x09\x04\x00\x00\x1c"
	"\x00\x4a\x00\x66\x00\x4a\x00\xb0\x00\x01\x00\x33\x00\x64\x00\x32"
	"\x00\x36\x00\x37\x00\x39\x00\x35\x00\x34\x00\x2d\x00\x65\x00\x65"
	"\x00\x62\x00\x37\x00\x2d\x00\x31\x00\x31\x00\x64\x00\x31\x00\x2d"
	"\x00\x62\x00\x39\x00\x34\x00\x65\x00\x2d\x00\x30\x00\x30\x00\x63"
	"\x00\x30\x00\x34\x00\x66\x00\x61\x00\x33\x00\x30\x00\x38\x00\x30"
	"\x00\x64\x00\x00\x00\x33\x00\x64\x00\x32\x00\x36\x00\x37\x00\x39"
	"\x00\x35\x00\x34\x00\x2d\x00\x65\x00\x65\x00\x62\x00\x37\x00\x2d"
	"\x00\x31\x00\x31\x00\x64\x00\x31\x00\x2d\x00\x62\x00\x39\x00\x34"
	"\x00\x65\x00\x2d\x00\x30\x00\x30\x00\x63\x00\x30\x00\x34\x00\x66"
	"\x00\x61\x00\x33\x00\x30\x00\x38\x00\x30\x00\x64\x00\x00\x00\x00"
	"\x00\x00\x10\x00\x80\x64\x00\x00\x00\x00\x00\x30\x6e\x06\x09\x2b"
	"\x06\x01\x04\x01\x82\x37\x12\x06\x01\x01\xff\x04\x5e\x00\x30\x00"
	"\x00\x00\x00\x0e\x00\x3e\x00\x52\x00\x4f\x00\x44\x00\x45\x00\x4e"
	"\x00\x54\x00\x00\x00\x37\x00\x38\x00\x34\x00\x34\x00\x30\x00\x2d"
	"\x00\x30\x00\x30\x00\x36\x00\x2d\x00\x35\x00\x38\x00\x36\x00\x37"
	"\x00\x30\x00\x34\x00\x35\x00\x2d\x00\x37\x00\x30\x00\x33\x00\x34"
	"\x00\x37\x00\x00\x00\x57\x00\x4f\x00\x52\x00\x4b\x00\x47\x00\x52"
	"\x00\x4f\x00\x55\x00\x50\x00\x00\x00\x00\x00\x30\x25\x06\x03\x55"
	"\x1d\x23\x01\x01\xff\x04\x1b\x30\x19\xa1\x10\xa4\x0e\x52\x00\x4f"
	"\x00\x44\x00\x45\x00\x4e\x00\x54\x00\x00\x00\x82\x05\x01\x00\x00"
	"\x00\x02\x30\x09\x06\x05\x2b\x0e\x03\x02\x1d\x05\x00\x03\x82\x01"
	"\x01\x00\x2e\xeb\xc7\x0d\xb8\x1d\x47\x11\x9d\x09\x88\x9b\x51\xdc"
	"\x45\xdd\x56\x51\xe2\xd1\x23\x11\x39\x9b\x2d\xda\xc7\xfe\x7a\xd7"
	"\x84\xe3\x3d\x54\x77\x97\x4d\x19\x92\x30\x64\xa0\x47\xc6\x2f\x6d"
	"\x93\xd2\x64\x7c\x76\xc8\x26\x45\xad\x5a\x44\x54\xea\xf6\x4b\x28"
	"\x77\x1f\x77\xea\xec\x74\x02\x38\x68\x9e\x79\x14\x72\x83\x34\x74"
	"\x62\xd2\xc1\x0c\xa4\x0b\xf2\xa9\xb0\x38\xbb\x7c\xd0\xae\xbe\xbf"
	"\x74\x47\x16\xa0\xa2\xd3\xfc\x1d\xb9\xba\x26\x10\x06\xef\xba\x1d"
	"\x43\x01\x4e\x4e\x6f\x56\xca\xe0\xee\xd0\xf9\x4e\xa6\x62\x63\xff"
	"\xda\x0b\xc9\x15\x61\x6c\xed\x6b\x0b\xc4\x58\x53\x86\x0f\x8c\x0c"
	"\x1a\x2e\xdf\xc1\xf2\x43\x48\xd4\xaf\x0a\x78\x36\xb2\x51\x32\x28"
	"\x6c\xc2\x75\x79\x3f\x6e\x99\x66\x88\x3e\x34\xd3\x7f\x6d\x9d\x07"
	"\xe4\x6b\xeb\x84\xe2\x0a\xbb\xca\x7d\x3a\x40\x71\xb0\xbe\x47\x9f"
	"\x12\x58\x31\x61\x2b\x9b\x4a\x9a\x49\x8f\xe5\xb4\x0c\xf5\x04\x4d"
	"\x3c\xce\xbc\xd2\x79\x15\xd9\x28\xf4\x23\x56\x77\x9f\x38\x64\x3e"
	"\x03\x88\x92\x04\x26\x76\xb9\xb5\xdf\x19\xd0\x78\x4b\x7a\x60\x40"
	"\x23\x91\xf1\x15\x22\x2b\xb4\xe7\x02\x54\xa9\x16\x21\x5b\x60\x96"
	"\xa9\x5c\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x01\x00\x00\x00\x0e\x00\x0e\x00\x6d\x69\x63\x72\x6f\x73"
	"\x6f\x66\x74\x2e\x63\x6f\x6d\x00";

/* Client New License Request (341 bytes) */

BYTE client_new_license_request[341] =
	"\x13\x83\x55\x01\x01\x00\x00\x00\x00\x00\x01\x04\xdc\x73\xa0\xc8"
	"\x69\x25\x6b\x18\xaf\x0b\x94\x7a\xa9\xa5\x20\xaf\x8b\xbc\x0d\xcc"
	"\xa3\x95\xb7\xb9\xeb\x81\x5d\xbe\x0a\x10\x9c\xd8\x02\x00\x08\x01"
	"\xda\x9c\x5d\xa6\x68\x9d\xa3\x90\x67\x24\xf3\x3a\xea\xa1\xe2\x68"
	"\xad\x12\xf5\xf6\x0b\x7a\xac\x92\xb1\x69\x6f\x42\x55\x8a\xa0\xe2"
	"\x9b\x2c\xd0\xc7\xee\x33\x6c\x47\x79\xc3\x1e\xbf\x03\x8b\x95\x70"
	"\x07\xa2\xbe\xee\x54\x02\x68\xf8\x90\xd7\xfe\x2c\x08\xe1\x6b\x2d"
	"\xff\x94\x76\x72\x5f\x7a\x76\x75\x32\x55\xcc\x58\x61\x63\xa5\x64"
	"\xf1\x6e\xc3\x07\x81\x82\x6f\x88\x73\x62\xfc\x28\x65\x91\xc2\xc8"
	"\x9f\x05\xb0\xd3\x93\x12\xbf\x6a\x50\x18\x99\x2d\x4d\xc4\x7f\x74"
	"\xd3\x30\x9f\x16\x78\xa5\xdf\xaa\x83\x65\x4f\x77\x30\x42\xe0\xd7"
	"\x69\xc8\x4d\xa5\x73\x11\x59\x35\xb9\xa7\xe2\xb0\xf6\xe3\xb9\x39"
	"\xc3\xd4\xe4\x6b\xca\x40\x9a\xac\x66\xe6\x1a\xa4\x1b\x39\x7e\x09"
	"\xe3\x72\x99\xdd\x90\x62\x55\x97\xa9\x04\xc7\x51\xaa\xa2\x01\xcb"
	"\x5a\x63\x4d\x1a\xe5\x99\xc3\xb1\x2a\x73\xe8\x9a\x00\x46\x92\x59"
	"\x39\xa3\x80\xa1\xac\x90\x52\xea\x63\x81\x49\x7d\xf3\x2d\x5c\xc3"
	"\x19\x9f\xed\xfe\x81\x1d\x8c\x04\x1c\xd9\x23\xd2\x6d\x80\x84\xf3"
	"\x00\xf2\xb1\x69\x2f\xcd\xb3\x9f\x69\xee\x60\x3e\x4b\xb5\xbe\x5a"
	"\x09\x83\x0b\xbc\x3d\x3e\x05\x47\x65\x96\x31\x8c\x6b\xc5\xe6\xa0"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x0f\x00\x0e\x00\x41\x64\x6d\x69"
	"\x6e\x69\x73\x74\x72\x61\x74\x6f\x72\x00\x10\x00\x07\x00\x52\x4f"
	"\x44\x45\x4e\x54\x00";

/* Server Platform Challenge (38 bytes) */

BYTE server_platform_challenge[38] =
	"\x02\x03\x26\x00\xff\xff\xff\xff\x50\xf7\x0a\x00\x46\x37\x85\x54"
	"\x8e\xc5\x91\x34\x97\x5d\x78\x94\xad\x3b\x81\xda\x88\x18\x56\x0f"
	"\x3a\xd1\xf1\x03\xef\x35";

/* Client Platform Challenge Response (66 bytes) */

BYTE client_platform_challenge_response[66] =
	"\x15\x83\x42\x00\x01\x00\x12\x00\xfa\xb4\xe8\x24\xcf\x56\xb2\x4e"
	"\x80\x02\xbd\xb6\x61\xfc\xdf\xe9\x6c\x44\x01\x00\x14\x00\xf8\xb5"
	"\xe8\x25\x3d\x0f\x3f\x70\x1d\xda\x60\x19\x16\xfe\x73\x1a\x45\x7e"
	"\x02\x71\x38\x23\x62\x5d\x10\x8b\x93\xc3\xf1\xe4\x67\x1f\x4a\xb6"
	"\x00\x0a";

BYTE license_server_modulus[256] =
	"\x88\xad\x7c\x8f\x8b\x82\x76\x5a\xbd\x8f\x6f\x62\x18\xe1\xd9\xaa"
	"\x41\xfd\xed\x68\x01\xc6\x34\x35\xb0\x29\x04\xca\x4a\x4a\x1c\x7e"
	"\x80\x14\xf7\x8e\x77\xb8\x25\xff\x16\x47\x6f\xbd\xe2\x34\x3d\x2e"
	"\x02\xb9\x53\xe4\x33\x75\xad\x73\x28\x80\xa0\x4d\xfc\x6c\xc0\x22"
	"\x53\x1b\x2c\xf8\xf5\x01\x60\x19\x7e\x79\x19\x39\x8d\xb5\xce\x39"
	"\x58\xdd\x55\x24\x3b\x55\x7b\x43\xc1\x7f\x14\x2f\xb0\x64\x3a\x54"
	"\x95\x2b\x88\x49\x0c\x61\x2d\xac\xf8\x45\xf5\xda\x88\x18\x5f\xae"
	"\x42\xf8\x75\xc7\x26\x6d\xb5\xbb\x39\x6f\xcc\x55\x1b\x32\x11\x38"
	"\x8d\xe4\xe9\x44\x84\x11\x36\xa2\x61\x76\xaa\x4c\xb4\xe3\x55\x0f"
	"\xe4\x77\x8e\xde\xe3\xa9\xea\xb7\x41\x94\x00\x58\xaa\xc9\x34\xa2"
	"\x98\xc6\x01\x1a\x76\x14\x01\xa8\xdc\x30\x7c\x77\x5a\x20\x71\x5a"
	"\xa2\x3f\xaf\x13\x7e\xe8\xfd\x84\xa2\x5b\xcf\x25\xe9\xc7\x8f\xa8"
	"\xf2\x8b\x84\xc7\x04\x5e\x53\x73\x4e\x0e\x89\xa3\x3c\xe7\x68\x5c"
	"\x24\xb7\x80\x53\x3c\x54\xc8\xc1\x53\xaa\x71\x71\x3d\x36\x15\xd6"
	"\x6a\x9d\x7d\xde\xae\xf9\xe6\xaf\x57\xae\xb9\x01\x96\x5d\xe0\x4d"
	"\xcd\xed\xc8\xd7\xf3\x01\x03\x38\x10\xbe\x7c\x42\x67\x01\xa7\x23";

BYTE license_server_exponent[4] = "\x00\x01\x00\x01";

BYTE terminal_server_modulus[256] =
	"\xc8\x90\x6b\xf0\xc6\x58\x81\xa6\x89\x1c\x0e\xf2\xf6\xd9\x82\x12"
	"\x71\xa5\x6e\x51\xdb\xe0\x32\x66\xaa\x91\x77\x0e\x88\xab\x44\xb7"
	"\xd3\x97\xda\x78\x8f\x0e\x44\x26\x46\x7f\x16\xd4\xc6\x63\xeb\xca"
	"\x55\xe5\x4e\x8b\x2d\xa6\x6d\x83\x95\xa7\xa8\x6a\xfa\xd0\xbe\x26"
	"\x80\xae\xab\x0a\x64\x90\x32\x8c\xdf\x5c\xf8\xf9\xd0\x7e\xd1\x6b"
	"\x3a\x29\x7e\x7d\xbd\x02\xa3\x86\x6c\xfd\xa5\x35\x71\xda\x21\xb4"
	"\xee\xa4\x97\xf3\xa8\xb2\x12\xdb\xa4\x27\x57\x36\xc9\x08\x22\x5c"
	"\x54\xf7\x99\x7b\xa3\x2f\xb8\x5c\xd5\x16\xb8\x19\x27\x6b\x71\x97"
	"\x14\x5b\xe8\x1f\x23\xe8\x5c\xb8\x1b\x73\x4b\x6e\x7a\x03\x13\xff"
	"\x97\xe9\x62\xb9\x4a\xa0\x51\x23\xc3\x6c\x32\x3e\x02\xf2\x63\x97"
	"\x23\x1c\xc5\x78\xd8\xfc\xb7\x07\x4b\xb0\x56\x0f\x74\xdf\xc5\x56"
	"\x28\xe4\x96\xfd\x20\x8e\x65\x5a\xe6\x45\xed\xc1\x05\x3e\xab\x58"
	"\x55\x40\xaf\xe2\x47\xa0\x4c\x49\xa3\x8d\x39\xe3\x66\x5f\x93\x33"
	"\x6d\xf8\x5f\xc5\x54\xe5\xfb\x57\x3a\xde\x45\x12\xb5\xc7\x05\x4b"
	"\x88\x1f\xb4\x35\x0f\x7c\xc0\x75\x17\xc6\x67\xdd\x48\x80\xcb\x0a"
	"\xbe\x9d\xf6\x93\x60\x65\x34\xeb\x97\xaf\x65\x6d\xdf\xbf\x6f\x5b";

BYTE terminal_server_exponent[4] = "\x00\x01\x00\x01";

BYTE client_random[32] =
	"\xdc\x73\xa0\xc8\x69\x25\x6b\x18\xaf\x0b\x94\x7a\xa9\xa5\x20\xaf"
	"\x8b\xbc\x0d\xcc\xa3\x95\xb7\xb9\xeb\x81\x5d\xbe\x0a\x10\x9c\xd8";

BYTE server_random[32] =
	"\x84\xef\xae\x20\xb1\xd5\x9e\x36\x49\x1a\xe8\x2e\x0a\x99\x89\xac"
	"\x49\xa6\x47\x4f\x33\x9b\x5a\xb9\x95\x03\xa6\xc6\xc2\x3c\x3f\x61";

BYTE premaster_secret[48] =
	"\xcf\x7a\xdb\xcb\xfb\x0e\x15\x23\x87\x1c\x84\x81\xba\x9d\x4e\x15"
	"\xbb\xd2\x56\xbd\xd8\xf7\xf3\x16\xcc\x35\x3b\xe1\x93\x42\x78\xdd"
	"\x92\x9a\xe4\x7a\xe2\x99\xd4\x73\xb1\xaa\x6f\x55\x94\x3b\xc9\xbc";

BYTE encrypted_premaster_secret[264] =
	"\xda\x9c\x5d\xa6\x68\x9d\xa3\x90\x67\x24\xf3\x3a\xea\xa1\xe2\x68"
	"\xad\x12\xf5\xf6\x0b\x7a\xac\x92\xb1\x69\x6f\x42\x55\x8a\xa0\xe2"
	"\x9b\x2c\xd0\xc7\xee\x33\x6c\x47\x79\xc3\x1e\xbf\x03\x8b\x95\x70"
	"\x07\xa2\xbe\xee\x54\x02\x68\xf8\x90\xd7\xfe\x2c\x08\xe1\x6b\x2d"
	"\xff\x94\x76\x72\x5f\x7a\x76\x75\x32\x55\xcc\x58\x61\x63\xa5\x64"
	"\xf1\x6e\xc3\x07\x81\x82\x6f\x88\x73\x62\xfc\x28\x65\x91\xc2\xc8"
	"\x9f\x05\xb0\xd3\x93\x12\xbf\x6a\x50\x18\x99\x2d\x4d\xc4\x7f\x74"
	"\xd3\x30\x9f\x16\x78\xa5\xdf\xaa\x83\x65\x4f\x77\x30\x42\xe0\xd7"
	"\x69\xc8\x4d\xa5\x73\x11\x59\x35\xb9\xa7\xe2\xb0\xf6\xe3\xb9\x39"
	"\xc3\xd4\xe4\x6b\xca\x40\x9a\xac\x66\xe6\x1a\xa4\x1b\x39\x7e\x09"
	"\xe3\x72\x99\xdd\x90\x62\x55\x97\xa9\x04\xc7\x51\xaa\xa2\x01\xcb"
	"\x5a\x63\x4d\x1a\xe5\x99\xc3\xb1\x2a\x73\xe8\x9a\x00\x46\x92\x59"
	"\x39\xa3\x80\xa1\xac\x90\x52\xea\x63\x81\x49\x7d\xf3\x2d\x5c\xc3"
	"\x19\x9f\xed\xfe\x81\x1d\x8c\x04\x1c\xd9\x23\xd2\x6d\x80\x84\xf3"
	"\x00\xf2\xb1\x69\x2f\xcd\xb3\x9f\x69\xee\x60\x3e\x4b\xb5\xbe\x5a"
	"\x09\x83\x0b\xbc\x3d\x3e\x05\x47\x65\x96\x31\x8c\x6b\xc5\xe6\xa0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

BYTE platform_challenge[10] = "\x54\x00\x45\x00\x53\x00\x54\x00\x00\x00";

void test_license(void)
{
	STREAM _s, *s;

	s = &_s;
	memcpy(license->client_random, client_random, sizeof(client_random));
	memcpy(license->premaster_secret, premaster_secret, sizeof(premaster_secret));

	s->data = server_license_request;
	s->p = s->data + LICENSE_PREAMBLE_LENGTH;
	license_read_license_request_packet(license, s);

#if 0
	printf("\n");

	printf("client random:\n");
	freerdp_hexdump(license->client_random, 32);
	printf("\n");

	printf("server random:\n");
	freerdp_hexdump(license->server_random, 32);
	printf("\n");

	printf("premaster secret:\n");
	freerdp_hexdump(license->premaster_secret, 48);
	printf("\n");

	printf("master secret:\n");
	freerdp_hexdump(license->master_secret, 48);
	printf("\n");

	printf("session key blob:\n");
	freerdp_hexdump(license->session_key_blob, 48);
	printf("\n");

	printf("licensing encryption key:\n");
	freerdp_hexdump(license->licensing_encryption_key, 16);
	printf("\n");

	printf("mac salt key:\n");
	freerdp_hexdump(license->mac_salt_key, 16);
	printf("\n");

	printf("modulus:\n");
	freerdp_hexdump(license->certificate->cert_info.modulus.data,
			license->certificate->cert_info.modulus.length);
	printf("\n");

	printf("exponent:\n");
	freerdp_hexdump(license->certificate->cert_info.exponent, 4);
	printf("\n");

	printf("encrypted premaster secret:\n");
	freerdp_hexdump(license->encrypted_premaster_secret->data,
			license->encrypted_premaster_secret->length);
	printf("\n");
#endif

	s->data = server_platform_challenge;
	s->p = s->data + LICENSE_PREAMBLE_LENGTH;
	license_read_platform_challenge_packet(license, s);
}

BYTE test_client_random[32] =
	"\xdc\x73\xa0\xc8\x69\x25\x6b\x18\xaf\x0b\x94\x7a\xa9\xa5\x20\xaf"
	"\x8b\xbc\x0d\xcc\xa3\x95\xb7\xb9\xeb\x81\x5d\xbe\x0a\x10\x9c\xd8";

BYTE test_server_random[32] =
	"\x16\x7e\xf8\x71\x48\x16\x1a\x4f\xa5\x2c\xcd\x73\x63\x60\xa6\xc3"
	"\xb9\x19\x1b\x4b\x6b\xb2\x0a\xb8\xec\xf1\x8d\x95\x4e\xa8\x21\xc5";

BYTE test_premaster_secret[48] =
	"\xcf\x7a\xdb\xcb\xfb\x0e\x15\x23\x87\x1c\x84\x81\xba\x9d\x4e\x15"
	"\xbb\xd2\x56\xbd\xd8\xf7\xf3\x16\xcc\x35\x3b\xe1\x93\x42\x78\xdd"
	"\x92\x9a\xe4\x7a\xe2\x99\xd4\x73\xb1\xaa\x6f\x55\x94\x3b\xc9\xbc";

BYTE test_modulus[64] =
	"\x23\xc9\xec\x0e\x9f\x1e\x0e\x1a\x78\xaf\xa5\x14\xd4\xf5\x45\xe4"
	"\x04\x6e\xf4\x01\xe9\xdf\x45\xd1\xc2\xae\xf4\x7f\xd3\xb9\xcb\xf3"
	"\x1a\x23\xa1\x0d\x4b\xd4\xd1\x4a\xd2\xd1\xc9\x7c\xab\x24\x8b\xb1"
	"\x5a\x93\xca\x34\x44\x17\xb5\xe4\xfe\xf7\x9a\xaa\x72\x0d\x41\x95";

BYTE test_exponent[4] = "\x01\x00\x01\x00";

BYTE test_master_secret[48] =
	"\xbe\x51\xee\x63\x23\x90\xd0\xf4\x3a\xce\x3a\x37\x65\xc3\xdd\xcf"
	"\xed\xf0\xc8\x19\xed\x77\x33\x4e\xfd\x2b\x7d\x5a\xe2\xca\xf3\x0a"
	"\xf1\x16\xe5\x0c\x78\x59\x7e\xd4\x4b\x57\xce\x17\x60\x3a\x5a\xb3";

BYTE test_session_key_blob[48] =
	"\x07\x4f\xa0\x2e\xee\xc4\x5a\x46\x21\x8c\xae\x01\x45\x02\x26\xe4"
	"\x54\x6b\x59\x10\xcc\x5b\xd1\x96\xd0\x5c\xeb\xc2\x96\x9b\x44\x7b"
	"\x1c\xd9\x66\xb1\x9e\x24\xaa\x60\x4f\x89\xd1\x4e\xf8\xb9\x55\x3b";

BYTE test_mac_salt_key[16] =
	"\x07\x4f\xa0\x2e\xee\xc4\x5a\x46\x21\x8c\xae\x01\x45\x02\x26\xe4";

BYTE test_licensing_encryption_key[16] =
	"\xf3\xb1\xe0\x3b\xfe\xb4\xf2\xc5\x28\xa9\x48\xcd\x90\xf1\x93\xe5";

BYTE test_encrypted_premaster_secret[64] =
	"\x6b\xbc\x77\x9f\x20\x0c\x98\x39\xc1\x85\x77\xc8\x19\x87\xd8\x82"
	"\x93\xbd\x21\x69\x5f\x87\xe0\xd6\x4e\xad\x5e\x23\x13\x80\x8c\x63"
	"\x3e\xd6\x6e\x60\xc9\x40\xe9\x86\x08\x8c\xd5\xaa\xa9\x54\xfe\x27"
	"\x4c\x1f\x87\x57\xde\xca\xd4\xc7\x1e\x46\x9e\x00\x7a\xdb\x47\x23";

void test_license_generate_keys(void)
{
	STREAM _s, *s;

	s = &_s;
	memcpy(license->client_random, client_random, sizeof(client_random));
	memcpy(license->server_random, test_server_random, sizeof(test_server_random));
	memcpy(license->premaster_secret, premaster_secret, sizeof(premaster_secret));
	memcpy(license->certificate->cert_info.exponent, test_exponent, sizeof(test_exponent));
	memcpy(license->certificate->cert_info.Modulus, test_modulus, sizeof(test_modulus));
	license->certificate->cert_info.ModulusLength = sizeof(test_modulus);

	license_generate_keys(license);
	license_encrypt_premaster_secret(license);

	s->data = license->master_secret;
	s->p = s->data + sizeof(test_master_secret);
	ASSERT_STREAM(s, test_master_secret, sizeof(test_master_secret));

	s->data = license->session_key_blob;
	s->p = s->data + sizeof(test_session_key_blob);
	ASSERT_STREAM(s, test_session_key_blob, sizeof(test_session_key_blob));

	s->data = license->mac_salt_key;
	s->p = s->data + sizeof(test_mac_salt_key);
	ASSERT_STREAM(s, test_mac_salt_key, sizeof(test_mac_salt_key));

	s->data = license->licensing_encryption_key;
	s->p = s->data + sizeof(test_licensing_encryption_key);
	ASSERT_STREAM(s, test_licensing_encryption_key, sizeof(test_licensing_encryption_key));

	s->data = license->encrypted_premaster_secret->data;
	s->p = s->data + sizeof(test_encrypted_premaster_secret);
	ASSERT_STREAM(s, test_encrypted_premaster_secret, sizeof(test_encrypted_premaster_secret));
}

void test_license_encrypt_premaster_secret(void)
{
	STREAM _s, *s;

	s = &_s;
	memcpy(license->premaster_secret, premaster_secret, sizeof(premaster_secret));
	memcpy(license->certificate->cert_info.exponent, test_exponent, sizeof(test_exponent));
	memcpy(license->certificate->cert_info.Modulus, test_modulus, sizeof(test_modulus));
	license->certificate->cert_info.ModulusLength = sizeof(test_modulus);

	s->data = license->encrypted_premaster_secret->data;
	s->p = s->data + sizeof(test_encrypted_premaster_secret);
	ASSERT_STREAM(s, test_encrypted_premaster_secret, sizeof(test_encrypted_premaster_secret));
}

BYTE test_encrypted_platform_challenge[10] =
	"\x84\x0a\x42\x50\xad\x5e\xc1\x29\x30\xbd";

BYTE test_platform_challenge[10] =
	"\x54\x00\x45\x00\x53\x00\x54\x00\x00\x00";

void test_license_decrypt_platform_challenge(void)
{
	STREAM _s, *s;

	s = &_s;
	memcpy(license->licensing_encryption_key, test_licensing_encryption_key,
			sizeof(test_licensing_encryption_key));

	license->encrypted_platform_challenge->data =
			(BYTE*) malloc(sizeof(test_encrypted_platform_challenge));
	license->encrypted_platform_challenge->length =
			sizeof(test_encrypted_platform_challenge);

	memcpy(license->encrypted_platform_challenge->data, test_encrypted_platform_challenge,
			sizeof(test_encrypted_platform_challenge));

	license_decrypt_platform_challenge(license);

	s->data = license->platform_challenge->data;
	s->p = s->data + sizeof(test_platform_challenge);

	ASSERT_STREAM(s, test_platform_challenge, sizeof(test_platform_challenge));
}