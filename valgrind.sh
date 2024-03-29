#!/usr/bin/env bash
# Copyright (C) 2019  SCS Lab <scs-help@cs.iit.edu>, Hariharan
# Devarajan <hdevarajan@hawk.iit.edu>, Anthony Kougkas
# <akougkas@iit.edu>, Xian-He Sun <sun@iit.edu>
#
# This file is part of Iris
# 
# Iris is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU General Public
# License along with this program.  If not, see
# <http://www.gnu.org/licenses/>.

if [ $1 = "C" ]  
then  
    /usr/bin/gcc -ggdb main.c -std=c99 -Wall -Werror -o program && /usr/local/bin/valgrind ./program
elif [ $1 = "Cpp" ]  
then  
    /usr/bin/g++ -g -fPIC -std=c++11 main.cpp src/iris.h src/API.cpp src/utils/Buffer.cpp src/utils/Buffer.h src/POSIX.cpp src/POSIX.h src/S3.cpp src/S3.h src/MPIIO.cpp src/MPIIO.h src/HDF5.cpp src/HDF5.h src/PNETCDF.cpp src/PNETCDF.h src/metadata_manager/MetadataManagerFactory.cpp src/metadata_manager/MetadataManagerFactory.h src/utils/CacheManager.cpp src/utils/CacheManager.h src/API.h src/metadata_manager/IrisMetadataManager.cpp src/metadata_manager/IrisMetadataManager.h src/metadata_manager/POSIXMetadataManager.cpp src/metadata_manager/POSIXMetadataManager.h src/metadata_manager/MPIIOMetadataManager.cpp src/metadata_manager/MPIIOMetadataManager.h src/metadata_manager/HDF5MetadataManager.cpp src/metadata_manager/HDF5MetadataManager.h src/metadata_manager/S3MetadataManager.cpp src/metadata_manager/S3MetadataManager.h src/metadata_manager/PNETCDFMetadataManager.cpp src/metadata_manager/PNETCDFMetadataManager.h src/mapper/MapperFactory.cpp src/mapper/MapperFactory.h src/mapper/AbstractMapper.cpp src/mapper/AbstractMapper.h src/mapper/POSIXMapper.cpp src/mapper/POSIXMapper.h src/mapper/S3Mapper.cpp src/mapper/S3Mapper.h src/Bootstrap.cpp src/Bootstrap.h src/utils/DataCompactor.cpp src/utils/DataCompactor.h src/constants.h src/utils/PrefetcherFactory.cpp src/utils/PrefetcherFactory.h src/utils/AbstractPrefetcher.cpp src/utils/AbstractPrefetcher.h src/utils/FileSystemPrefetcher.cpp src/utils/FileSystemPrefetcher.h src/utils/ObjectStorePrefetcher.cpp src/utils/ObjectStorePrefetcher.h src/utils/AggregatorFactory.cpp src/utils/AggregatorFactory.h src/utils/AbstractAggregator.cpp src/utils/AbstractAggregator.h src/utils/FileSystemAggregator.cpp src/utils/FileSystemAggregator.h src/utils/ObjectStoreAggregator.cpp src/utils/ObjectStoreAggregator.h src/mapper/HDF5Mapper.cpp src/mapper/HDF5Mapper.h src/mapper/MPIIOMapper.cpp src/mapper/MPIIOMapper.h src/mapper/PNETCDFMapper.cpp src/mapper/PNETCDFMapper.h src/file_systems/FileSystemFactory.cpp src/file_systems/FileSystemFactory.h src/file_systems/AbstractFileSystem.cpp src/file_systems/AbstractFileSystem.h src/file_systems/PVFS2Client.cpp src/file_systems/PVFS2Client.h src/object_stores/ObjectStoreFactory.cpp src/object_stores/ObjectStoreFactory.h src/object_stores/AbstractObjectStore.cpp src/object_stores/AbstractObjectStore.h src/object_stores/HyperdexClient.cpp src/object_stores/HyperdexClient.h src/return_codes.h testing/local_tests.cpp testing/local_tests.h -L/usr/lib -lhyperdex-client -lhyperdex-admin -o program && /usr/bin/valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program
fi
