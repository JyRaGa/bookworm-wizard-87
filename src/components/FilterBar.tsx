import { useState } from 'react';
import { Input } from '@/components/ui/input';
import { Button } from '@/components/ui/button';
import { Select, SelectContent, SelectItem, SelectTrigger, SelectValue } from '@/components/ui/select';
import { Search, Filter } from 'lucide-react';
import { FilterOptions } from '@/types/book';

interface FilterBarProps {
  onFilter: (filters: FilterOptions) => void;
}

export const FilterBar = ({ onFilter }: FilterBarProps) => {
  const [author, setAuthor] = useState('');
  const [year, setYear] = useState('');
  const [genre, setGenre] = useState('');
  const [prompt, setPrompt] = useState('');

  const handleSearch = () => {
    onFilter({
      author: author || undefined,
      year: year ? parseInt(year) : undefined,
      genre: genre || undefined,
      prompt: prompt || undefined,
    });
  };

  const handleReset = () => {
    setAuthor('');
    setYear('');
    setGenre('');
    setPrompt('');
    onFilter({});
  };

  return (
    <div className="bg-card p-6 rounded-lg shadow-sm border space-y-4">
      <div className="flex items-center gap-2 mb-4">
        <Filter className="w-5 h-5 text-primary" />
        <h2 className="text-xl font-semibold">Filter Books</h2>
      </div>

      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-4">
        <Input
          placeholder="Search by author..."
          value={author}
          onChange={(e) => setAuthor(e.target.value)}
        />
        
        <Input
          type="number"
          placeholder="Published after year..."
          value={year}
          onChange={(e) => setYear(e.target.value)}
        />
        
        <Select value={genre} onValueChange={setGenre}>
          <SelectTrigger>
            <SelectValue placeholder="Select genre" />
          </SelectTrigger>
          <SelectContent>
            <SelectItem value="fiction">Fiction</SelectItem>
            <SelectItem value="classic">Classic</SelectItem>
            <SelectItem value="dystopian">Dystopian</SelectItem>
            <SelectItem value="science-fiction">Science Fiction</SelectItem>
            <SelectItem value="novel">Novel</SelectItem>
            <SelectItem value="story">Story</SelectItem>
          </SelectContent>
        </Select>

        <div className="flex gap-2">
          <Button onClick={handleSearch} className="flex-1">
            <Search className="w-4 h-4 mr-2" />
            Search
          </Button>
          <Button onClick={handleReset} variant="outline">
            Reset
          </Button>
        </div>
      </div>

      <div className="pt-2">
        <Input
          placeholder="Describe the book you're looking for..."
          value={prompt}
          onChange={(e) => setPrompt(e.target.value)}
          onKeyDown={(e) => e.key === 'Enter' && handleSearch()}
          className="text-base"
        />
        <p className="text-xs text-muted-foreground mt-2">
          Try: "A book about time travel" or "Mystery novel set in Victorian era"
        </p>
      </div>
    </div>
  );
};
