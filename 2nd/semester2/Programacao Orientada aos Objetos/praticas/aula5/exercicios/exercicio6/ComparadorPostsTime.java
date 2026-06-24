import java.util.Comparator;

public class ComparadorPostsTime implements Comparator<FBPost> {
    @Override
    public int compare(FBPost post1,FBPost post2) {
        return post1.getTime().compareTo(post2.getTime());
    }


}
