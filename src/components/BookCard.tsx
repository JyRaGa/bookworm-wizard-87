import { Book } from '@/types/book';
import { Card, CardContent, CardFooter } from '@/components/ui/card';
import { Badge } from '@/components/ui/badge';
import { Star } from 'lucide-react';

interface BookCardProps {
  book: Book;
  onClick?: () => void;
}

export const BookCard = ({ book, onClick }: BookCardProps) => {
  return (
    <Card 
      className="book-card-hover cursor-pointer overflow-hidden group"
      onClick={onClick}
    >
      <div className="aspect-[2/3] overflow-hidden bg-muted">
        <img 
          src={book.coverImage} 
          alt={book.title}
          className="w-full h-full object-cover transition-transform duration-300 group-hover:scale-105"
        />
      </div>
      <CardContent className="p-4">
        <h3 className="font-semibold text-lg line-clamp-2 mb-1">
          {book.title}
        </h3>
        <p className="text-sm text-muted-foreground mb-2">
          {book.author}
        </p>
        <div className="flex items-center gap-1 mb-3">
          <Star className="w-4 h-4 fill-accent text-accent" />
          <span className="text-sm font-medium">{book.rating}</span>
        </div>
        <div className="flex flex-wrap gap-1">
          {book.genre.slice(0, 2).map(genre => (
            <Badge key={genre} variant="secondary" className="text-xs">
              {genre}
            </Badge>
          ))}
        </div>
      </CardContent>
      <CardFooter className="p-4 pt-0">
        <p className="text-xs text-muted-foreground">
          Published: {book.year}
        </p>
      </CardFooter>
    </Card>
  );
};
