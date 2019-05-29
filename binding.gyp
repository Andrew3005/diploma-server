{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "cflags": [ "x64", "-std=c++11"],
      "target_name": "result",
      "sources": [ "main.cpp" ],
      "type": "shared_library"
    }
  ]
}