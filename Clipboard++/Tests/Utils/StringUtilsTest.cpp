#include <gtest/gtest.h>
#include "StringUtils.h" 

TEST(ReplaceAllTest, ReplacesAllOccurrences)
{
    std::string original = "uno dos uno tres uno";
    const std::string from = "uno";
    const std::string to = "cuatro";
    std::string expected = "cuatro dos cuatro tres cuatro";
    //Remember original will change
    StringUtils::replaceAll(original, from, to);

    EXPECT_EQ(original, expected);
}

TEST(ReplaceAllTest, HandlesOverlappingAndEmptyCases)
{

    std::string original = "ababab";
    std::string expected_overlap = "axabab"; 

    StringUtils::replaceAll(original, "aba", "axa");
    EXPECT_EQ(original, expected_overlap);
    
    std::string original_empty_to = "a-b-c";
    std::string expected_empty_to = "abc";


    StringUtils::replaceAll(original_empty_to, "-", "");
    EXPECT_EQ(original_empty_to, expected_empty_to);
}

TEST(EscapeHtmlTest, EscapesAllSpecialCharacters)
{
    const std::string original = "<h1>\"Hello & World\"</h1>";
    const std::string expected = "&lt;h1&gt;&quot;Hello &amp; World&quot;&lt;/h1&gt;";

    std::string result = StringUtils::escapeHtml(original);

    EXPECT_EQ(result, expected);
}

TEST(EscapeHtmlTest, HandlesAmpersandCorrectlyFirst)
{
    const std::string original = "Este texto ya tiene un &amp; y un <.";
    const std::string expected = "Este texto ya tiene un &amp;amp; y un &lt;.";

    std::string result = StringUtils::escapeHtml(original);

    EXPECT_EQ(result, expected);
}