{
  	"targets": [
		{
	    	"target_name": "bridge",
	    	'include_dirs': ['../amo-library'],
			'sources' : ['bridge.cpp'],
			"cflags": ["-Wall","-std=c++11"],  
			"conditions": [ 
		        [ 'OS=="mac"', { 
		            "xcode_settings": { 
		                'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++'], 
		                'OTHER_LDFLAGS': ['-stdlib=libc++'], 
		                'MACOSX_DEPLOYMENT_TARGET': '10.7' },
					"sources" : ['<!@(ls -1 ../amo-library/*.cpp)','<!@(ls -1 ../amo-library/calculator/*.cpp)'] 
		            }
		        ], 
		        [ 'OS=="win"', { 
					"sources" : ['<!@(dir /b ../amo-library/*.cpp)','<!@(dir /b ../amo-library/calculator/*.cpp)'] 
		            }
		        ] 
	       	] 
	    }
	]	
}
