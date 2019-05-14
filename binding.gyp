{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "result",
      "sources": [ "main.cpp" ]
    }
  ]
}