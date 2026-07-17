import java.io.File
import java.util.concurrent.TimeUnit

fun readGitVersion(name: String): String {
    val version = "git rev-parse HEAD".runCommand().trim()
    return GIT_VERSION_TEMPLATE.format(version, name)
}

fun String.runCommand(): String {
    val parts = this.split("\\s".toRegex())
    val proc =
        ProcessBuilder(*parts.toTypedArray())
            .directory(File("."))
            .redirectOutput(ProcessBuilder.Redirect.PIPE)
            .redirectError(ProcessBuilder.Redirect.PIPE)
            .start()

    proc.waitFor(2, TimeUnit.SECONDS)
    return proc.inputStream.bufferedReader().readText()
}
