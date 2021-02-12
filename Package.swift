// swift-tools-version:5.3
import PackageDescription


let package = Package(
    name: "FMVideoRecordKit",
    platforms: [
        .iOS(.v11)
    ],
    products: [
        .library(name: "FMVideoRecordKit", type: .dynamic, targets: ["FMVideoRecordKit"])        
    ],
    targets: [
        .target(name: "FMVideoRecordKit", path:"FMVideoRecordKit", publicHeadersPath:"FMVideoRecordKit", exclude: ["FMVideoRecordingDemo ","README.md"])
    ]
)
